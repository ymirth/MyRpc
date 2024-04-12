## A simple RPC framework based on Muduo
基于 Muduo 网络库实现 TCP 通信，使用 Protocol Buffers 进行数据交换，使用 Zookeeper 服务注册中间件开发

### 描述
- 实现服务映射表，实现服务的发布和查找
- 用 Protocol Buffers 设计 RPC 服务接口和协议格式
- 使用 Muduo 提供 RPC 服务端和客户端的网络通信
- 使用 Zookeeper 作为服务注册中心，实现服务的注册和发现
- 使用无锁循环队列作为日志队列，实现异步日志记录


### 环境
- zookeeper 3.4.13
- protobuf 3.6.1
- muduo 2.0

### 协议格式
```cpp
/*
    |---raw data ---|----------------------------serialized data------------------------|
    |  header_size  |               rpc header                  |       rpc request     |
    |               | (service_name, method_name, request_size) |                       |
    |    4 bytes    |              header_size bytes            |  request_size bytes   |
*/
```


### 使用
#### 发布 RPC 服务
- 定义 RPC 服务接口
    ```proto
        // protobuf版本
        syntax = "proto3"; 

        // 包名，在C++中表现为命名空间
        package example;

        // 生成service服务类的描述，默认不生成
        option cc_generic_services=true;


        // 定义数据结构（消息），1,2指字段标识号，可以理解为字段占位序号
        message ResultCode
        {
            int32 errcode = 1;
            bytes errmsg = 2;
        }

        message LoginRequest
        {
            bytes name=1;
            bytes pwd=2;
        }

        message LoginResponse
        {
            ResultCode result=1;  // 复合message
            bool success = 2;
        }

        // 定义用户模块相关RPC接口
        service UserRpcService
        {
            rpc Login(LoginRequest) returns(LoginResponse);
        }
    ```

- 实现 RPC 服务接口
    ```cpp
        #include <iostream>
        #include "example.service.pb.h"
        #include "rpcapplication.h"
        #include "rpcprovider.h"

        class UserService : public example::UserRpcService
        {
        public:
            bool Login(const std::string &name, const std::string pwd)
            {
                std::cout << "local service: Login" << std::endl;
                std::cout << "name:" << name << "pwd: " << pwd << std::endl; 
                return pwd == "123";
            }

            // Closure关闭，终止
            void Login(::google::protobuf::RpcController *controller,
                    const ::example::LoginRequest *request,
                    ::example::LoginResponse *response,
                    ::google::protobuf::Closure *done)
            {
                // 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
                std::string name = request->name();
                std::string pwd = request->pwd();

                // 做本地业务
                bool ret = Login(name, pwd);
                response->set_success(ret);

                // 把响应写入  包括错误码、错误消息、返回值
                example::ResultCode *result_code = response->mutable_result();
                result_code->set_errcode(0);
                result_code->set_errmsg("");

                // 执行回调操作   执行响应对象数据的序列化和网络发送（都是由框架来完成的）
                done->Run();
            };
        };

        int main(int argc, char **argv)
        {
            RpcApplication::init(argc, argv);
            std::cout << RpcApplication::getInstance().getConfig().getIP() << std::endl;
            RpcProvider provider;
            provider.publishService(new UserService());
            provider.run();

            return 0;
        };

    ```

#### 调用 RPC 服务
```cpp
    #include <iostream>
    #include "example.service.pb.h"
    #include "rpcapplication.h"
    #include "rpcclient.h"

    int main(int argc, char **argv)
    {
        RpcApplication::init(argc, argv);
        RpcClient client;
        client.connect();

        example::UserRpcService_Stub stub(&client);

        example::LoginRequest request;
        request.set_name("zhang san");
        request.set_pwd("123");

        example::LoginResponse response;
        stub.Login(NULL, &request, &response, NULL);

        if (response.success())
        {
            std::cout << "login success" << std::endl;
        }
        else
        {
            std::cout << "login failed" << std::endl;
        }

        return 0;
    };
```

**测试**

```shell
./test.sh
```    

**参考**
- https://github.com/wangzyon/mpzRPC