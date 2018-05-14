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

bool NodeManager::Launch(
        const std::string& supervisorAddress,
        ResourceInfo resourceInfo)
{
    mResourceLoader->LoadResource(resourceInfo);
    const std::string& entrance = resourceInfo.entrance();
    mLauncher->Launch(
            entrance,
            std::vector<std::string> {supervisorAddress, resourceInfo.dstlocation()}); // NOLINT
    return true;
}

} // namespace framework
