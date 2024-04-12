#include<memory>

#include <google/protobuf/message.h>
#include <muduo/base/AsyncLogging.h>

#include "rpcprovider.h"
#include "rpcapplication.h"
#include "zookeeperutil.h"

#include "rpcheader.pb.h"
#include "logger.h"


void RpcProvider::run()
{
    // 读取Rpc配置,获取工厂对象信息
    std::string ip = RpcApplication::getInstance().getConfig().getIP();
    uint16_t port = RpcApplication::getInstance().getConfig().getPort();
    int muduoThreadNum = RpcApplication::getInstance().getConfig().getMuduoThreadNum();
    
    // 构建TcpServer对象
    muduo::net::InetAddress address(ip, port);
    muduo::net::EventLoop loop;
    muduo::net::TcpServer server(&loop, address, "RpcProvider");

    // 设置连接回调
    server.setConnectionCallback(std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
    // 设置消息回调
    server.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1, 
                                                                        std::placeholders::_2,
                                                                         std::placeholders::_3));
    server.setThreadNum(muduoThreadNum);
    
    // 注册在zookeeper上
    // 1. 连接zookeeper
    ZkClient zkCli;
    zkCli.Start();
    // 2. 创建节点
    for(auto& [service_name, service_info]: m_service_map){
        std::string service_path = "/" + service_name;
        zkCli.Create(service_path.c_str(), nullptr, 0, 0); // ZOO_EPHEMERAL表示临时节点
        
        for(auto& [method_name, method_desc]: service_info.m_method_map){
            std::string method_path = service_path + "/" + method_name; 
            char buf[64] = {0};
            snprintf(buf, sizeof(buf), "%s:%d", ip.c_str(), port);

            zkCli.Create(method_path.c_str(), buf, strlen(buf), ZOO_EPHEMERAL);

            LOG_INFO("register service: %s method: %s at: %s", service_name.c_str(), method_name.c_str(), method_path.c_str());
        }
    }
    
    // 启动server, 接受请求
    server.start();
    loop.loop();
}

void RpcProvider::publishService(::google::protobuf::Service *service)
{
    // service的描述信息
    const ::google::protobuf::ServiceDescriptor *desc = service->GetDescriptor();
    // service的名字
    std::string serviceName = desc->full_name();
    // 获取service的方法数量
    int methodCnt = desc->method_count();


    ServiceInfo serviceInfo;

    // 初始化serviceInfo
    serviceInfo.m_service = service;
    // 遍历service的所有方法
    for(int i = 0; i < methodCnt; i++){
        // 获取方法的描述信息
        const ::google::protobuf::MethodDescriptor *methodDesc = desc->method(i);
        // 获取方法的名字
        std::string methodName = methodDesc->name();
        // 将方法名和方法描述信息加入到map中
        serviceInfo.m_method_map[methodName] = methodDesc;
    }
    
    m_service_map[serviceName] = serviceInfo;
}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    if(!conn->connected()){
        conn->shutdown();
    }
}


// 反序列化request数据
static void parseRpcRequest(const std::string &rpcRequest,uint32_t& header_size, rpcheader::rpcheader &header, std::string & request_str)
{
    /*
        |---raw data ---|----------------------------serialized data------------------------|
        |  header_size  |              header class                 |   request string      |
        |               | (service_name, method_name, request_size) |                       |
        |    4 bytes    |              header_size bytes            |  request_size bytes   |
    */

    // 解析数据header
    std::string header_str;
    // rpcRequest.copy((char *)&header_size, 4, 0);  // 读取4字节数据，未被序列化
    header_size = (uint32_t)std::stoi(rpcRequest.substr(0, 4));  // 读取4字节数据，未被序列化
    header_str = rpcRequest.substr(4, header_size);
    
    // 解析header_str
    if(!header.ParseFromString(header_str)){
        LOG_ERROR("parse header_str failed\n");
        return;
    }

    // 解析request_str
    uint32_t request_size = header.request_size();
    request_str = rpcRequest.substr(4 + header_size, request_size); 

    // 打印调试信息
    // std::cout << "============================================" << std::endl;
    // std::cout << "header_size: " << header_size << std::endl;
    // std::cout << "rpc_header_str: " << header_str << std::endl;
    // std::cout << "service_name: " << header.service_name() << std::endl;
    // std::cout << "method_name: " << header.method_name() << std::endl;
    // std::cout << "args_str: " << request_str << std::endl;
    // std::cout << "============================================" << std::endl;

}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &conn,
                            muduo::net::Buffer *buf,
                            muduo::Timestamp time)
{
    /*
        |---raw data ---|----------------------------serialized data------------------------|
        |  header_size  |              header class                 |   request string      |
        |               | (service_name, method_name, request_size) |                       |
        |    4 bytes    |              header_size bytes            |  request_size bytes   |
    */

    // 读取接收到的数据
    std::string recv_str = buf->retrieveAllAsString();

    uint32_t header_size = 0;
    rpcheader::rpcheader header;
    std::string rpc_request_str;
    parseRpcRequest(recv_str, header_size, header, rpc_request_str);

    std::string service_name = header.service_name();
    std::string method_name = header.method_name();
  
    // 获取 rpc 服务注册表中的 service
    google::protobuf::Service* const service = getService(service_name);
    if(service == nullptr){
        LOG_ERROR("unknown service: %s\n", service_name.c_str() );
        return;
    }
    // 获取 rpc 服务注册表中的 service 提供的 method descriptor
    const google::protobuf::MethodDescriptor* const method_desc = getMethodDescriptor(service_name, method_name);
    if(method_desc == nullptr){
        LOG_ERROR("unknown method: %s\n", method_name.c_str());
        return;
    }

    
    // 生成rpc方法的请求request和响应response
    google::protobuf::Message *request = service->GetRequestPrototype(method_desc).New();
    
    if(!request->ParseFromString(rpc_request_str)){
        LOG_ERROR("parse request message failed\n");
        return;
    }

    google::protobuf::Message *response = service->GetResponsePrototype(method_desc).New();

    // 回调函数
    google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider,
                                                                     const muduo::net::TcpConnectionPtr &,
                                                                     google::protobuf::Message*>(this,
                                                                                                 &RpcProvider::sendResponse,
                                                                                                 conn,
                                                                                                 response);
    
    // Service类callmethod通过method des找到Service重载的对应方法，并传递controller/request/response/done  
    service->CallMethod(method_desc, nullptr, request, response, done);   
}

// done中的回调函数，用于序列化rpc方法调用的响应response参数，并通过网络发送给rpc调用方
void RpcProvider::sendResponse(const muduo::net::TcpConnectionPtr &conn,
                               google::protobuf::Message* responseMessage)
{
    std::string send_str;
    if(!responseMessage->SerializeToString(&send_str)){
        LOG_ERROR("serialize response message failed\n");
    }else{
        conn->send(send_str);
    }
    conn->shutdown();
}
