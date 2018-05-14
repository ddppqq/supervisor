// Copyright (c) 2018 DAI

#include "framework/nodemanager/local_resource_loader.h"

#include "framework/common/local_filesystem.h"

namespace framework {

LocalResrouceLoader::LocalResrouceLoader()
{
    mFileSystem = new common::LocalFileSystem();
}

LocalResrouceLoader::~LocalResrouceLoader()
{
    delete mFileSystem;
}

bool LocalResrouceLoader::LoadResource(const ResourceInfo& resourceInfo)
{
    const std::string& src = resourceInfo.srclocation();
    const std::string& dst = resourceInfo.dstlocation();
    return mFileSystem->Copy(src, dst);
}

} // namespace framework
