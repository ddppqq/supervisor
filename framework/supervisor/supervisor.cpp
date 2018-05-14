// Copyright (c) 2018, DAI

#include <pthread.h>
#include <unistd.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include "framework/nodemanager/node_manager.h"
#include "framework/supervisor/supervisor.h"
#include "framework/supervisor/supervisor_service_impl.h"

namespace framework {

pthread_once_t once = PTHREAD_ONCE_INIT;

Supervisor::Supervisor()
{
    mNodeManager = new NodeManager();
}

Supervisor::~Supervisor()
{
    delete mNodeManager;
}

int Supervisor::Run()
{
    return ::pthread_once(&once, Supervisor::StartRpcServer);
}

int Supervisor::Start(const ResourceInfo& resourceInfo)
{
    if (!mNodeManager) {
        return -1;
    }
    return mNodeManager->Launch("abc", ResourceInfo());
}

int Supervisor::Stop(std::string processId)
{
    if (processId.empty() || !mSubprocesses.count(processId)) {
        return -1;
    }
    return mSubprocesses[processId]->GetService()->Stop();
}

ProcessInfo Supervisor::GetProcessInfo(std::string processId)
{
    if (processId.empty() || !mSubprocesses.count(processId)) {
        return ProcessInfo();
    }
    return mSubprocesses[processId]->GetService()->GetProcessInfo();
}

void Supervisor::StartRpcServer()
{
    std::string address("0.0.0.0:50051");
    SupervisorServiceImpl service;

    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(address, ::grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << address << std::endl;
    server->Wait();
}

} // namespace framework
