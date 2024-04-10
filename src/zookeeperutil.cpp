#include <iostream>
#include <exception>

#include <semaphore.h>

#include "zookeeperutil.h"
#include "rpcconfig.h"
#include "rpcapplication.h"

// 全局watcher   zkserver --- notifiy ---> zkclient
void global_watcher(zhandle_t *zh, int type, int state,
                    const char *path, void *watcherCtx)
{
    if (type == ZOO_SESSION_EVENT)
    {
        if (state == ZOO_CONNECTED_STATE)
        {
            sem_t *sem = (sem_t *)zoo_get_context(zh);
            sem_post(sem);
        }
    }
}

ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle);
    }
}

void ZkClient::Start()
{
    // zk的客户端配置
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    // 获取配置
    std::string ip = RpcApplication::getInstance().getConfig().getZookeeperIP();
    int port = RpcApplication::getInstance().getConfig().getZookeeperPort();
    std::string host = ip + ":" + std::to_string(port);
    int timeout = 30000;
    /*
        zookeeper_init(host, fn, recv_timeout, clientid, context, flags)
        host: zk服务器地址, 格式“ip:port, ip:port, ip:port”
        fn: watcher回调函数
        recv_timeout: 超时时间
        clientid: 客户端id
        context: 传递给watcher回调函数的参数
        flags: 0
    */
    
    // 注册watcher回调函数
    m_zhandle = zookeeper_init(host.c_str(), global_watcher, timeout, nullptr, nullptr, 0);
    if (m_zhandle == nullptr)
    {
        throw std::runtime_error("zookeeper_init failed");
    }

    sem_t sem;
    sem_init(&sem, 0, 0);              // __pshared: 0, __value: 0 表示线程间共享, 初始值为0
    zoo_set_context(m_zhandle, &sem);  // 设置上下文,用于watcher回调函数
    sem_wait(&sem);                    // 阻塞等待, 直到sem_post(&sem)被调用
    std::cout<<"zookeeper connected"<<std::endl;
}

void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    // // 先判断是否已经创建，若创建了则不重复创建
    // char buffer[64] = {0};
    // int bufferlen = sizeof(buffer);
    // int flag = zoo_exists(m_zhandle, path, 0, nullptr);
    // if(flag == ZNODEEXISTS) return;

    // ZOO_OPEN_ACL_UNSAFE: 不安全的acl权限
    int ret = zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, nullptr, 0);
    if (ret == ZNODEEXISTS)
    {
        std::cout << "Znode already exists" << std::endl;
    }
    else if (ret != ZOK)
    {
        throw std::runtime_error("zoo_create failed");
    }
}

std::string ZkClient::GetData(const char *path)
{
    char buffer[64] = {0};
    int bufferlen = sizeof(buffer);
    int ret = zoo_get(m_zhandle, path, 0, buffer, &bufferlen, nullptr);
    if (ret != ZOK)
    {
        throw std::runtime_error("zoo_get failed");
    }
    return buffer;
}
    




