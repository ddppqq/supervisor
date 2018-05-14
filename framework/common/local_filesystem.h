// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_COMMON_LOCAL_FILESYSTEM_H
#define FRAMEWORK_COMMON_LOCAL_FILESYSTEM_H

#include <string>
#include "framework/common/abstract_filesystem.h"

namespace common {

class LocalFileSystem : public AbstractFileSystem
{
public:
    virtual ~LocalFileSystem() {}
    virtual bool Copy(const std::string& src, const std::string& dst);
    virtual std::string GetFileName(const std::string& path);
    virtual std::string GetPathName(const std::string& path);
    virtual bool IsFile(const std::string& path);
    virtual bool IsFileExist(const std::string& path);
    virtual bool CreateDirectory(const std::string& path);

protected:
    bool CopyFile(const std::string& src, const std::string& dst);
    std::string AppendSlash(const std::string& src);
};

} // namespace common
#endif // FRAMEWORK_COMMON_LOCAL_FILESYSTEM_H
