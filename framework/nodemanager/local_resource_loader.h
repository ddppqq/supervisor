// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_LOCAL_RESOURCE_LOADER_H
#define FRAMEWORK_NODEMANAGER_LOCAL_RESOURCE_LOADER_H

#include <string>
#include "framework/common/abstract_filesystem.h"
#include "framework/nodemanager/abstract_resource_loader.h"

namespace framework {

class LocalResrouceLoader : public AbstractResourceLoader
{
public:
    LocalResrouceLoader();
    virtual ~LocalResrouceLoader();
    bool LoadResource(const ResourceInfo& resourceInfo);

private:
    common::AbstractFileSystem* mFileSystem;
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_LOCAL_RESOURCE_LOADER_H
