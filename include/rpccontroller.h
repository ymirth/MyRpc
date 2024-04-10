#pragma once

#include <string>
#include <google/protobuf/service.h>



class CustomRpcController : public google::protobuf::RpcController
{
public:
    CustomRpcController(): m_failed(false), m_error_text(""){}
    void Reset() override;
    bool Failed() const override;
    std::string ErrorText() const override;
    
    void StartCancel() override;
    
    void SetFailed(const std::string &reason) override;
    
    bool IsCanceled() const override;
    void NotifyOnCancel(google::protobuf::Closure *callback) override;


private:
    bool m_failed;
    std::string m_error_text;
};
    