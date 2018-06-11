// Copyright (c) 2018 DAI

#include "framework/nodemanager/node_manager.h"

#include "framework/nodemanager/local_fork_launcher.h"
#include "framework/nodemanager/local_resource_loader.h"

namespace framework {

NodeManager::NodeManager()
{
    mResourceLoader = new LocalResrouceLoader();
    mLauncher = new LocalForkLauncher();
}

NodeManager::~NodeManager()
{
    delete mResourceLoader;
    delete mLauncher;
}

std::pair<int, AbstractProcessDescriptor*> NodeManager::Launch(
        const std::string& supervisorAddress,
        const ResourceInfo& resourceInfo)
{
    mResourceLoader->LoadResource(resourceInfo);
    const std::string& entrance = resourceInfo.entrance();
    AbstractProcessDescriptor* descriptor = new BinarySubprocessDescriptor();
    int s = mLauncher->Launch(
            entrance,
            std::vector<std::string> {supervisorAddress, descriptor->GetProcessId()}); // NOLINT
    return std::pair<int, AbstractProcessDescriptor*>(s, descriptor);
}

} // namespace framework
