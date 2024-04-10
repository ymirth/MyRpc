#pragma once
#ifndef RPC_CONFIG_H
#define RPC_CONFIG_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>


class RpcConfig
{
public:
    void loadConfig(const std::string &configFile);
    
    std::string operator[](const std::string &key){ return m_config_dict[key]; }    
    std::string getConfig(const std::string &key){ return m_config_dict[key];}
    void setConfig(const std::string &key, const std::string &value){ m_config_dict[key] = value; }

    std::vector<std::string> getConfigKeys(){
        std::vector<std::string> keys;
        for(auto it = m_config_dict.begin(); it != m_config_dict.end(); it++){
            keys.push_back(it->first);
        }
        return keys;
    }

    std::string getIP(){ return m_config_dict["rpcserverip"]; }
    int getPort(){ return std::stoi(m_config_dict["rpcserverport"]); }
    std::string getZookeeperIP(){ return m_config_dict["zookeeperip"]; }
    int getZookeeperPort(){ return std::stoi(m_config_dict["zookeeperport"]); }
    int getMuduoThreadNum(){ return std::stoi(m_config_dict["muduothreadnum"]); }

private:
    std::unordered_map<std::string ,std::string> m_config_dict;
};




#endif // RPC_CONFIG_H
