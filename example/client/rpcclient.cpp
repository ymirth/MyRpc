#include <iostream>
#include "rpcapplication.h"
#include "example.service.pb.h"
#include "rpcchannel.h"

int main(int argc, char **argv)
{
    // 整个程序启动以后，想使用mpzrpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    RpcApplication::init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    example::UserRpcService_Stub stub(new CustomRpcChannel());

    // rpc方法的请求参数
    example::LoginRequest request;
    request.set_name("Xiangrui Yu");
    request.set_pwd("123456");
    // rpc方法的响应
    example::LoginResponse response;
    // 发起rpc方法的调用  同步的rpc调用过程  MpzrpcChannel::callmethod
    stub.Login(nullptr, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读调用的结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    return 0;
}