#include <string>
#include <functional>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include"rpcchannel.h"
#include"rpcapplication.h"
#include"zookeeperutil.h"
#include"logger.h"

#include"rpcheader.pb.h"


// 生成序列化请求数据
static std::string generate_request_data(const google::protobuf::MethodDescriptor *method,
                                  const google::protobuf::Message *request)
{
    //1. 序列化请求
    std::string request_str;
    if(!request->SerializeToString(&request_str)){
        LOG_ERROR("serialize request message failed\n");
        return "";
    }

    //2. 获取rpc请求头, 并序列化
    rpcheader::rpcheader rpc_header;
    rpc_header.set_service_name(method->service()->full_name());
    rpc_header.set_method_name(method->name());
    rpc_header.set_request_size(request_str.size());

    std::string header_str;
    if(!rpc_header.SerializeToString(&header_str)){
        LOG_ERROR("serialize header message failed\n");
        return "";
    }

    //3. 组装rpc请求数据, 在消息头部插入4字节的header长度
    std::string header_size = std::to_string(static_cast<uint32_t>(header_str.size()));
    std::string send_str = header_size + header_str + request_str;
    send_str.insert(0, 4 - header_size.size(), '0');

    return send_str;
}

// 获取zookeeper中服务的地址
static void host_from_zk(const std::string &method_path, std::string& host, uint16_t& port)
{
    // 获取配置文件中的zk地址
    ZkClient zk_client;
    zk_client.Start();
    // 获取服务对应的URL
    std::string host_data = zk_client.GetData(method_path.c_str());
    // 解析host_data
    size_t pos = host_data.find(":");
    if(pos == std::string::npos){
        LOG_ERROR("host_data format error\n");
    }
    host = host_data.substr(0, pos);
    port = static_cast<uint16_t>(std::stoi(host_data.substr(pos + 1)));
}

void CustomRpcChannel::CallMethod(const google::protobuf::MethodDescriptor * method,
                                   google::protobuf::RpcController * controller,
                                      const google::protobuf::Message * request,
                                        google::protobuf::Message * response,
                                            google::protobuf::Closure * done)
{
    // 获取序列化rpc_request
    std::string send_str = generate_request_data(method, request);

    // 获取带调用服务的名称 /UserServiceRpc/method
    std::string method_path = "/" + method->service()->full_name() + "/" + method->name();
    std::string host;
    uint16_t port;
    host_from_zk(method_path, host, port);

    // 建立连接
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1){
        LOG_ERROR("create socket failed\n");
        return;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); // 网络字节序
    server_addr.sin_addr.s_addr = inet_addr(host.c_str());

    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        LOG_ERROR("connect server failed\n");
        return;
    }

    // 发送rpc_request
    if(send(client_fd, send_str.c_str(), send_str.size(), 0) == -1){
        LOG_ERROR("send data failed\n");
        return;
    }

    // 接受rpc_response
    char recv_buf[1024] = {0};  // 不用std::string, 防止/0截断
    int recv_size = recv(client_fd, recv_buf, 1024, 0);
    if(recv_size == -1){
        LOG_ERROR("recv data failed\n");
        ::close(client_fd);
        return;
    }

    // 反序列化rpc_response
    if(!response->ParseFromArray(recv_buf, recv_size)){
        LOG_ERROR("parse response message failed\n");
        ::close(client_fd);
        return;
    }

    ::close(client_fd);
}



