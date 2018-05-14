// Copyright (c) 2018, DAI

#include <grpcpp/grpcpp.h>
#include "framework/supervisor/supervisor_service_impl.h"

namespace framework {

SupervisorServiceImpl::SupervisorServiceImpl()
{
}

::grpc::Status SupervisorServiceImpl::Start(
        ::grpc::ServerContext* context,
        const ::LaunchProcessRequest* request,
        ::LaunchProcessResponse* response)
{
    return ::grpc::Status::OK;
}

::grpc::Status SupervisorServiceImpl::Stop(
        ::grpc::ServerContext* context,
        const ::StopProcessRequest* request,
        ::StopProcessResponse* response)
{
    return ::grpc::Status::OK;
}
::grpc::Status SupervisorServiceImpl::ListProcesses(
        ::grpc::ServerContext* context,
        const ::ListProcessesInfoRequest* request,
        ::ListProcessesInfoResponse* response)
{
    return ::grpc::Status::OK;
}

} // namespace framework
