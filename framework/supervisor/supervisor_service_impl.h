// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUPERVISOR_SUPERVISOR_SERVICE_IMPL_H
#define FRAMEWORK_SUPERVISOR_SUPERVISOR_SERVICE_IMPL_H

#include <grpcpp/grpcpp.h>

#include "protocol/supervisor.grpc.pb.h"

namespace framework {

class SupervisorServiceImpl final : public SupervisorService::Service
{
public:
    SupervisorServiceImpl();
    ~SupervisorServiceImpl() {}
    ::grpc::Status Start(
            ::grpc::ServerContext* context,
            const ::LaunchProcessRequest* request,
            ::LaunchProcessResponse* response);
    ::grpc::Status Stop(
            ::grpc::ServerContext* context,
            const ::StopProcessRequest* request,
            ::StopProcessResponse* response);
    ::grpc::Status ListProcesses(
            ::grpc::ServerContext* context,
            const ::ListProcessesInfoRequest* request,
            ::ListProcessesInfoResponse* response);
};

} // namespace framework
#endif // FRAMEWORK_SUPERVISOR_SUPERVISOR_SERVICE_IMPL_H
