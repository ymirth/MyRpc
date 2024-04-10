#include "rpccontroller.h"

void CustomRpcController::Reset()
{
    m_failed = false;
    m_error_text = "";
}

bool CustomRpcController::Failed() const
{
    return m_failed;
}

std::string CustomRpcController::ErrorText() const
{
    return m_error_text;
}

void CustomRpcController::StartCancel()
{
    // do nothing
}

void CustomRpcController::SetFailed(const std::string &reason)
{
    m_failed = true;
    m_error_text = reason;
}

bool CustomRpcController::IsCanceled() const
{
    return false;
}

void CustomRpcController::NotifyOnCancel(google::protobuf::Closure *callback)
{
    // do nothing
}

