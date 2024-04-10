#include"rpcconfig.h"
#include <string>
#include <iostream>
#include <fstream>

void RpcConfig::loadConfig(const std::string &configFile)
{
    std::fstream file(configFile);
    if(!file.is_open()){
        std::cerr << "config file open error\n";
        exit(1);
    }
    nlohmann::json j;
    file >> j;
    m_config_dict["rpcserverip"] = j["rpcserverip"];
    m_config_dict["rpcserverport"] = std::to_string(int(j["rpcserverport"]));
    m_config_dict["zookeeperip"] = j["zookeeperip"];
    m_config_dict["zookeeperport"] = std::to_string(int(j["zookeeperport"]));
    m_config_dict["muduothreadnum"] = std::to_string(int(j["muduothreadnum"]));
}


