// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_CLIENT_CLIENT_H
#define FRAMEWORK_CLIENT_CLIENT_H

#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>
#include <vector>
#include "framework/client/abstract_client.h"
#include "protocol/supervisor.grpc.pb.h"

namespace framework {

class Client : public AbstractClient
{
public:
    explicit Client(std::shared_ptr<::grpc::Channel> channel);
    virtual ~Client() {}
    virtual ::grpc::Status Start(const ResourceInfo& resourceInfo);
    virtual ::grpc::Status Stop(const std::string& processId);
    virtual ::grpc::Status ListProcesses(
            const std::string& processIdPrefix,
            std::vector<ProcessInfo>* infos);
    virtual std::string Ping(const std::string& msg);
    bool Heartbeat(const ProcessInfo& processInfo);

private:
    std::unique_ptr<SupervisorService::Stub> mStub;
};

} // namespace framework
#endif // FRAMEWORK_CLIENT_CLIENT_H
