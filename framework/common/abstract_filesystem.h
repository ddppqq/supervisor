// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_COMMON_ABSTRACT_FILESYSTEM_H
#define FRAMEWORK_COMMON_ABSTRACT_FILESYSTEM_H

#include <string>

namespace common {

class AbstractFileSystem
{
public:
    virtual ~AbstractFileSystem() {}
    virtual bool Copy(const std::string& src, const std::string& dst) = 0;
    virtual std::string GetFileName(const std::string& path) = 0;
    virtual std::string GetPathName(const std::string& path) = 0;
    virtual bool IsFile(const std::string& path) = 0;
    virtual bool IsFileExist(const std::string& path) = 0;
    virtual bool CreateDirectory(const std::string& path) = 0;
};

} // namespace common
#endif // FRAMEWORK_COMMON_ABSTRACT_FILESYSTEM_H
