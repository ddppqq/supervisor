// Copyright (c) 2018, DAI

#include "framework/client/client.h"

namespace framework {

Client::Client(std::shared_ptr<::grpc::Channel> channel)
    : mStub(SupervisorService::NewStub(channel))
{
}

::grpc::Status Client::Start(const ResourceInfo& resourceInfo)
{
    ::grpc::ClientContext context;
    LaunchProcessRequest request;
    ResourceInfo* info = request.mutable_resourceinfo();
    info->set_srclocation(resourceInfo.srclocation());
    info->set_dstlocation(resourceInfo.dstlocation());
    info->set_entrance(resourceInfo.entrance());
    info->set_resourcetype(resourceInfo.resourcetype());
    LaunchProcessResponse response;
    return mStub->Start(&context, request, &response);
}

::grpc::Status Client::Stop(const std::string& processId)
{
    ::grpc::ClientContext context;
    StopProcessRequest request;
    request.set_processid(processId);
    StopProcessResponse response;
    return mStub->Stop(&context, request, &response);
}

::grpc::Status Client::ListProcesses(
        const std::string& processIdPrefix,
        std::vector<ProcessInfo>* infos)
{
    if (!infos) {
        return ::grpc::Status::CANCELLED;
    }
    ::grpc::ClientContext context;
    ListProcessesInfoRequest request;
    request.set_processidprefix(processIdPrefix);
    ListProcessesInfoResponse response;
    ::grpc::Status s = mStub->ListProcesses(&context, request, &response);
    if (s.ok()) {
        for (int i = 0; i < response.processesinfo_size(); ++i) {
            infos->push_back(response.processesinfo(i));
        }
    }
    return s;
}

std::string Client::Ping(const std::string& msg)
{
    ::grpc::ClientContext context;
    PingRequest request;
    request.set_request(msg);
    PingResponse response;
    if (mStub->Ping(&context, request, &response).ok()) {
        return response.response();
    }
    return "Ping failed";
}

bool Client::Heartbeat(const ProcessInfo& processInfo)
{
    ::grpc::ClientContext context;
    HeartbeatRequest request;
    request.CopyFrom(processInfo);
    HeartbeatResponse response;
    if (mStub->Heartbeat(&context, request, &response).ok()) {
        return true;
    }
    return false;
}

} // namespace framework
