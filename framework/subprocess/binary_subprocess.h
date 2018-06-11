// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUBPROCESS_BINARY_SUBPROCESS_H
#define FRAMEWORK_SUBPROCESS_BINARY_SUBPROCESS_H

#include <string>
#include "framework/client/client.h"
#include "framework/common/abstract_process_descriptor.h"
#include "framework/common/local_filesystem.h"
#include "protocol/common.pb.h"

namespace framework {

class BinarySubprocess : public AbstractSubprocess
{
public:
    BinarySubprocess(
            const std::string& parentIPPort,
            const std::string& processId);
    virtual ~BinarySubprocess();
    virtual void Run();
    virtual bool SendHeartbeatToParent();

private:
    Client* mClient;
};

} // namespace framework
#endif // FRAMEWORK_SUBPROCESS_BINARY_SUBPROCESS_H
