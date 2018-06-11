// Copyright (c) 2018, DAI

#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "framework/common/abstract_process_descriptor.h"
#include "framework/nodemanager/node_manager.h"
#include "framework/supervisor/supervisor_service_impl.h"

namespace {
const char* kServiceIPPort = "localhost:50051";
const int64_t kTriggerIntervalInMs = 1000000;
const int64_t kTimeoutIntervalInMs = 10000000;
framework::SupervisorServiceImpl* kService = NULL;
pthread_once_t kOnce = PTHREAD_ONCE_INIT;
pthread_mutex_t kLock = PTHREAD_MUTEX_INITIALIZER;

void* StartRpcServer(void* arg)
{
    if (!kService) {
        std::cout << "StartRpcServer failed" << std::endl;
        exit(1);
    }
    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(
            kServiceIPPort,
            ::grpc::InsecureServerCredentials());
    builder.RegisterService(kService);

    std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << kServiceIPPort << std::endl;
    server->Wait();
    return NULL;
}

void* StartHeartbeatTimer(void* arg)
{
    if (!kService) {
        std::cout << "StartHeartbeatTimer failed" << std::endl;
        exit(1);
    }
    while (true) {
        // sleep 1s
        sleep(1);
        kService->UpdateProcessesInfo();
        std::cout << "tick" << std::endl;
    }
    return NULL;
}

void* StartLaunchThread(void* arg)
{
    if (!kService) {
        std::cout << "StartHeartbeatTimer failed" << std::endl;
        exit(1);
    }
    while (true) {
        // sleep 1s
        sleep(1);
        kService->LaunchProcesses();
    }
}

void StartThreads()
{
    pthread_t rpcServer, heartbeat, launchThread;
    if (pthread_create(&rpcServer, NULL, &StartRpcServer, NULL)) {
        std::cout << "start thread StartRpcServer failed" << std::endl;
        exit(1);
    }
    if (pthread_create(&heartbeat, NULL, &StartHeartbeatTimer, NULL)) {
        std::cout << "start thread StartHeartbeatTimer failed" << std::endl;
        exit(1);
    }
    if (pthread_create(&launchThread, NULL, &StartLaunchThread, NULL)) {
        std::cout << "start thread StartLaunchThread failed" << std::endl;
        exit(1);
    }
    pthread_join(rpcServer, NULL);
    pthread_join(heartbeat, NULL);
    pthread_join(launchThread, NULL);
}

}

namespace framework {

SupervisorServiceImpl::SupervisorServiceImpl()
{
    mNodeManager = new NodeManager();
}

SupervisorServiceImpl::~SupervisorServiceImpl()
{
    delete mNodeManager;
}

::grpc::Status SupervisorServiceImpl::Start(
        ::grpc::ServerContext* context,
        const ::LaunchProcessRequest* request,
        ::LaunchProcessResponse* response)
{
    pthread_mutex_lock(&kLock);
    mToBeLaunchedProcesses.push_back(request->resourceinfo());
    pthread_mutex_unlock(&kLock);
    response->set_status(LaunchProcessStatus::LAUNCH_SUCCESS);
    return ::grpc::Status::OK;
}

::grpc::Status SupervisorServiceImpl::Stop(
        ::grpc::ServerContext* context,
        const ::StopProcessRequest* request,
        ::StopProcessResponse* response)
{
    pthread_mutex_lock(&kLock);
    const std::string& processId = request->processid();
    if (!mSubprocesses.count(processId)) {
        response->set_status(StopProcessStatus::FAILURE_PROCESS_NOT_EXIST);
        pthread_mutex_unlock(&kLock);
        return ::grpc::Status::CANCELLED;
    }
    delete mSubprocesses[processId];
    mSubprocesses.erase(processId);
    pthread_mutex_unlock(&kLock);
    response->set_status(StopProcessStatus::STOP_SUCCESS);
    return ::grpc::Status::OK;
}

::grpc::Status SupervisorServiceImpl::ListProcesses(
        ::grpc::ServerContext* context,
        const ::ListProcessesInfoRequest* request,
        ::ListProcessesInfoResponse* response)
{
    const std::string processIdPrefix = request->processidprefix();
    pthread_mutex_lock(&kLock);
    for (auto i : mSubprocesses) {
        if (i.first.find(processIdPrefix) == std::string::npos) {
            continue;
        }
        ProcessInfo* info = response->add_processesinfo();
        // TODO(dai): complete this
        info->set_processid(i.first);
        info->set_cpu(1);
        info->set_memory(2);
        info->set_disk(3);
        info->set_timesincestartedinms(0);
        info->set_processstatus(ProcessStatus::STARTING);
    }
    pthread_mutex_unlock(&kLock);
    return ::grpc::Status::OK;
}

::grpc::Status SupervisorServiceImpl::Heartbeat(
        ::grpc::ClientContext* context,
        const ::HeartbeatRequest& request,
        ::HeartbeatResponse* response)
{
    const ProcessInfo& info = request.processinfo();
    pthread_mutex_lock(&kLock);
    if (!mSubprocesses.count(info.processid())) {
        // ignore this response and subprocess will suicide
    } else {
        response->set_msg("ok");
        // TODO(dai): complete this process info
        mSubprocesses[info.processid()]->SetLastHeartbeatTimestampInMs(
                GetCurrentTimestampInMs());
    }
    pthread_mutex_unlock(&kLock);
    return ::grpc::Status::OK;
}

::grpc::Status SupervisorServiceImpl::Ping(
        ::grpc::ServerContext* context,
        const ::PingRequest* request,
        ::PingResponse* response)
{
    std::cout << "request msg is: " + request->request() << std::endl;
    response->set_response(request->request());
    return ::grpc::Status::OK;
}

void SupervisorServiceImpl::Run()
{
    kService = this;
    pthread_once(&kOnce, StartThreads);
}

void SupervisorServiceImpl::UpdateProcessesInfo()
{
    int64_t now = GetCurrentTimestampInMs();
    pthread_mutex_lock(&kLock);
    std::unordered_map<std::string, AbstractProcessDescriptor*>::iterator
        it = mSubprocesses.begin();
    while (it != mSubprocesses.end()) {
        if (now - it->second->GetLastHeartbeatTimestampInMs() > kTimeoutIntervalInMs) { // NOLINT
            delete it->second;
            it = mSubprocesses.erase(it);
        } else {
            ++it;
        }
    }
    pthread_mutex_unlock(&kLock);
}

void SupervisorServiceImpl::LaunchProcesses()
{
    pthread_mutex_lock(&kLock);
    std::vector<ResourceInfo> processes;
    processes.swap(mToBeLaunchedProcesses);
    pthread_mutex_unlock(&kLock);

    std::vector<std::pair<int, AbstractProcessDescriptor*> > processesStatus;
    for (auto i : processes) {
        processesStatus.push_back(mNodeManager->Launch(kServiceIPPort, i));
    }

    pthread_mutex_lock(&kLock);
    for (auto i : processesStatus) {
        mSubprocesses[i.second->GetProcessId()] = i.second;
    }
    pthread_mutex_unlock(&kLock);
}

int64_t SupervisorServiceImpl::GetCurrentTimestampInMs()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return int64_t(tv.tv_sec) * 1000 + int64_t(tv.tv_usec) / 1000;
}

} // namespace framework
