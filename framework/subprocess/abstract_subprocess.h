// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUBPROCESS_ABSTRACT_SUBPROCESS_H
#define FRAMEWORK_SUBPROCESS_ABSTRACT_SUBPROCESS_H

#include <string>
#include "protocol/common.pb.h"

namespace framework {

class AbstractSubprocess
{
public:
    explicit AbstractSubprocess(
            const std::string& parentIPPort,
            const std::string& processId)
    {
        mProcessId = processId;
        mParentIPPort = parentIPPort;
    }
    virtual ~AbstractSubprocess() {}
    virtual void Run() = 0;
    virtual bool SendHeartbeatToParent() = 0;
    ProcessInfo GetProcessInfo()
    {
        // TODO(dai): fill out other info here
        ProcessInfo info;
        info.set_processid(mProcessId);
        return info;
    }
    std::string GetParentIPPort()
    {
        return mParentIPPort;
    }

private:
    std::string mParentIPPort;
    std::string mProcessId;
};

} // namespace framework
#endif // FRAMEWORK_SUBPROCESS_ABSTRACT_SUBPROCESS_H
