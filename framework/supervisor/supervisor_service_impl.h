// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUPERVISOR_SUPERVISOR_SERVICE_IMPL_H
#define FRAMEWORK_SUPERVISOR_SUPERVISOR_SERVICE_IMPL_H

#include <grpcpp/grpcpp.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "protocol/supervisor.grpc.pb.h"

namespace framework {

class AbstractNodeManager;
class AbstractProcessDescriptor;

class SupervisorServiceImpl final : public SupervisorService::Service
{
public:
    SupervisorServiceImpl();
    virtual ~SupervisorServiceImpl();
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
    ::grpc::Status Heartbeat(
            ::grpc::ClientContext* context,
            const ::HeartbeatRequest& request,
            ::HeartbeatResponse* response);
    ::grpc::Status Ping(
            ::grpc::ServerContext* context,
            const ::PingRequest* request,
            ::PingResponse* response);
    void Run();
    void UpdateProcessesInfo();
    void LaunchProcesses();
    int64_t GetCurrentTimestampInMs();

private:
    std::unordered_map<std::string, AbstractProcessDescriptor*> mSubprocesses;
    std::vector<ResourceInfo> mToBeLaunchedProcesses;
    AbstractNodeManager* mNodeManager;
};

} // namespace framework
#endif // FRAMEWORK_SUPERVISOR_SUPERVISOR_SERVICE_IMPL_H
