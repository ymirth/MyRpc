#pragma once
#ifndef RPC_PROVIDER_H
#define RPC_PROVIDER_H

#include<muduo/net/TcpConnection.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/InetAddress.h>


#include <unordered_map>
#include <memory>
#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>


class RpcProvider{
public:
    void publishService(::google::protobuf::Service *service);
    void run();
private:
    void onConnection(const muduo::net::TcpConnectionPtr &conn);
    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buf,
                   muduo::Timestamp time);
    void onWriteComplete(const muduo::net::TcpConnectionPtr &conn);
    void sendResponse(const muduo::net::TcpConnectionPtr &conn,
                      google::protobuf::Message* responseMessage);


    google::protobuf::Service* const getService(const std::string &service_name){
        auto it = m_service_map.find(service_name);
        if(it == m_service_map.end()){
            return nullptr;
        }
        return it->second.m_service;
    }
                                                
    const google::protobuf::MethodDescriptor* const getMethodDescriptor(const std::string &service_name,
                                                                  const std::string &method_name){
        auto it = m_service_map.find(service_name);
        if(it == m_service_map.end()){
            return nullptr;
        }
        auto it_method = it->second.m_method_map.find(method_name);
        if(it_method == it->second.m_method_map.end()){
            return nullptr;
        }
        return it_method->second;
    }
    



    struct ServiceInfo
    {
        google::protobuf::Service *m_service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> m_method_map;
    };
    std::unordered_map<std::string, ServiceInfo> m_service_map;
};



#endif // !RPC_PROVIDER_H