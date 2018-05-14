// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_ABSTRACT_NODEMANAGER_H
#define FRAMEWORK_NODEMANAGER_ABSTRACT_NODEMANAGER_H

#include <string>
#include "protocol/common.pb.h"

namespace framework {

class AbstractNodeManager
{
public:
    virtual ~AbstractNodeManager() {}
    virtual bool Launch(
            const std::string& supervisorAddress,
            ResourceInfo resourceInfo) = 0;
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_ABSTRACT_NODEMANAGER_H
