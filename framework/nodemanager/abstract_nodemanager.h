// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_ABSTRACT_NODEMANAGER_H
#define FRAMEWORK_NODEMANAGER_ABSTRACT_NODEMANAGER_H

#include <string>
#include <utility>
#include "framework/common/abstract_process_descriptor.h"
#include "protocol/common.pb.h"

namespace framework {

class AbstractNodeManager
{
public:
    virtual ~AbstractNodeManager() {}
    virtual std::pair<int, AbstractProcessDescriptor*> Launch(
            const std::string& supervisorAddress,
            const ResourceInfo& resourceInfo) = 0;
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_ABSTRACT_NODEMANAGER_H
