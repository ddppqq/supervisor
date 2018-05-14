// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_ABSTRACT_RESOURCE_LOADER_H
#define FRAMEWORK_NODEMANAGER_ABSTRACT_RESOURCE_LOADER_H

#include <string>
#include "protocol/common.pb.h"

namespace framework {

class AbstractResourceLoader
{
public:
    virtual ~AbstractResourceLoader() {}
    virtual bool LoadResource(const ResourceInfo& resourceInfo) = 0;
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_ABSTRACT_RESOURCE_LOADER_H
