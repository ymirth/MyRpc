#pragma once
#ifndef RPC_APPLICATION_H
#define RPC_APPLICATION_H

#include <iostream>

#include "rpcconfig.h"

// 单例
class RpcApplication
{
public:
    static void init(int argc, char **argv)
    {
        if(argc != 3){
            std::cout<< "argc = " << argc << "\n";
            std::cout << "format: command -c <json config file>\n";
            exit(1);
        }
        if(std::string(argv[1]) != "-c"){
            std::cout << "format: command \"-c\" <json config file>\n";
            exit(1);
        }
        RpcConfig &config = RpcApplication::getConfig();
        config.loadConfig(argv[2]);
    }

    static RpcApplication& getInstance()
    {
        static RpcApplication instance;
        return instance;
    }

    static RpcConfig& getConfig()
    {
        static RpcConfig config;
        return config;   
    }
private:
    RpcApplication(){};
    ~RpcApplication(){};
    #pragma region delete copy and move
    RpcApplication(const RpcApplication &) = delete;
    RpcApplication &operator=(const RpcApplication &) = delete;
    RpcApplication(RpcApplication &&) = delete;
    RpcApplication &operator=(RpcApplication &&) = delete;
    #pragma endregion
};



#endif // !RPC_APPLICATION_H