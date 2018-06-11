// Copyright (c) 2018, DAI

#include "framework/subprocess/binary_subprocess.h"

#include <pthread.h>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include <sys/time.h>

namespace {
framework::AbstractSubprocess* kSubprocess = NULL;
pthread_once_t kOnce = PTHREAD_ONCE_INIT;
const int64_t kTimeoutIntervalInMs = 10000000;
int64_t GetCurrentTimestampInMs()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return int64_t(tv.tv_sec) * 1000 + int64_t(tv.tv_usec) / 1000;
}

void* StartHeartbeatTimer(void* arg)
{
    if (!kSubprocess) {
        std::cout << "StartHeartbeatTimer failed" << std::endl;
        exit(1);
    }
    int64_t lastHeartbeat = GetCurrentTimestampInMs();
    while (true) {
        // sleep 1s
        sleep(1);
        if (kSubprocess->SendHeartbeatToParent()) {
            lastHeartbeat = GetCurrentTimestampInMs();
        } else if (GetCurrentTimestampInMs() - lastHeartbeat >
                kTimeoutIntervalInMs) {
            std::cout << "suicide" << std::endl;
            exit(1);
        }
        std::cout << "tick" << std::endl;
    }
    return NULL;
}

void StartThreads()
{
    pthread_t heartbeat;
    if (pthread_create(&heartbeat, NULL, &StartHeartbeatTimer, NULL)) {
        std::cout << "start thread StartHeartbeatTimer failed" << std::endl;
        exit(1);
    }
    pthread_join(heartbeat, NULL);
}

} // anonymous namespace

namespace framework {

BinarySubprocess::BinarySubprocess(
        const std::string& parentIPPort,
        const std::string& processId)
    : AbstractSubprocess(parentIPPort, processId)
{
   mClient = new Client(::grpc::CreateChannel(parentIPPort, ::grpc::InsecureChannelCredentials())); // NOLINT
}

BinarySubprocess::~BinarySubprocess()
{
    delete mClient;
}

void BinarySubprocess::Run()
{
    kSubprocess = this;
    pthread_once(&kOnce, StartThreads);
}

bool BinarySubprocess::SendHeartbeatToParent()
{
    return mClient->Heartbeat(GetProcessInfo());
}

} // namespace framework
