// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_NODE_MANAGER_H
#define FRAMEWORK_NODEMANAGER_NODE_MANAGER_H

#include <string>
#include <utility>
#include "framework/nodemanager/abstract_launcher.h"
#include "framework/nodemanager/abstract_nodemanager.h"
#include "framework/nodemanager/abstract_resource_loader.h"
#include "protocol/common.pb.h"

namespace framework {

class NodeManager : public AbstractNodeManager
{
public:
    NodeManager();
    ~NodeManager();
    std::pair<int, AbstractProcessDescriptor*> Launch(
            const std::string& supervisorAddress,
            const ResourceInfo& resourceInfo);

private:
    AbstractResourceLoader* mResourceLoader;
    AbstractLauncher* mLauncher;
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_NODE_MANAGER_H
