// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUPERVISOR_ABSTRACT_SUPERVISOR_H
#define FRAMEWORK_SUPERVISOR_ABSTRACT_SUPERVISOR_H

#include <string>
#include "protocol/common.pb.h"

namespace framework {

class AbstractSupervisor
{
public:
    virtual ~AbstractSupervisor() {}
    virtual int Run() = 0;
    virtual int Start(const ResourceInfo& resourceInfo) = 0;
    virtual int Stop(std::string processId) = 0;
    virtual ProcessInfo GetProcessInfo(std::string processId) = 0;
};

} // namespace framework
#endif // FRAMEWORK_SUPERVISOR_ABSTRACT_SUPERVISOR_H
