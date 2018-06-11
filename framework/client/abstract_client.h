// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_CLIENT_ABSTRACT_CLIENT_H
#define FRAMEWORK_CLIENT_ABSTRACT_CLIENT_H

#include <string>
#include <vector>
#include "protocol/common.pb.h"

namespace framework {

class AbstractClient
{
public:
    virtual ~AbstractClient() {}
    virtual ::grpc::Status Start(const ResourceInfo& resourceInfo) = 0;
    virtual ::grpc::Status Stop(const std::string& processId) = 0;
    virtual ::grpc::Status ListProcesses(
            const std::string& processIdPrefix,
            std::vector<ProcessInfo>* infos) = 0;
    virtual std::string Ping(const std::string& msg) = 0;
};

} // namespace framework
#endif // FRAMEWORK_CLIENT_ABSTRACT_CLIENT_H
