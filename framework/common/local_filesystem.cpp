// Copyright (c) 2018, DAI

#include "framework/common/local_filesystem.h"

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

namespace {
const int kBlock = 4096;
}

namespace common {

bool LocalFileSystem::Copy(const std::string& src, const std::string& dst)
{
    if (src.empty() || dst.empty()) {
        return false;
    }
    if (IsFile(src)) {
        return CopyFile(src, dst);
    }
    DIR *d;
    struct dirent *t;
    if ((d = opendir(src.c_str())) == NULL) {
        return false;
    }
    const std::string& srcPath = AppendSlash(GetPathName(src));
    const std::string& dstPath = AppendSlash(dst);
    while ((t = readdir(d)) != NULL) { // NOLINT
        if (std::string(t->d_name) == "." || std::string(t->d_name) == "..") {
            continue;
        }
        if (IsFile(srcPath + t->d_name)) {
            CreateDirectory(dst);
            CopyFile(srcPath + t->d_name, dstPath + t->d_name);
        } else {
            CreateDirectory(dst + t->d_name);
            Copy(srcPath + t->d_name, dst + t->d_name);
        }
    }
    return true;
}

std::string LocalFileSystem::GetFileName(const std::string& path)
{
    if (path.empty() || !IsFile(path)) {
        return "";
    }
    return path.substr(path.rfind('/') + 1);
}

std::string LocalFileSystem::GetPathName(const std::string& path)
{
    if (path.empty()) {
        return "";
    }
    if (IsFile(path)) {
        return AppendSlash(path.substr(0, path.rfind('/')));
    }
    return AppendSlash(path);
}

bool LocalFileSystem::IsFile(const std::string& path)
{
    if (path.empty()) {
        return false;
    }
    struct stat s;
    if (lstat(path.c_str(), &s) == -1) {
        return false;
    }
    return S_ISREG(s.st_mode);
}

bool LocalFileSystem::CopyFile(const std::string& src, const std::string& dst)
{
    if (src.empty() || !IsFileExist(src)) {
        return false;
    }
    int fdSrc = -1, fdDst = -1;
    if ((fdSrc = open(src.c_str(), O_RDONLY)) == -1) {
        return false;
    }

    std::string dstPath = dst[dst.length() - 1] == '/' ?
        dst + GetFileName(src) : dst;
    if ((fdDst = open(dstPath.c_str(), O_CREAT | O_TRUNC | O_RDWR)) == -1) {
        close(fdSrc);
        return false;
    }

    char block[kBlock] = {0};
    int nRead = 0;
    while ((nRead = read(fdSrc, block, kBlock)) != 0) {
        if (write(fdDst, block, nRead) == -1) {
            close(fdSrc);
            close(fdDst);
            return false;
        }
    }

    if (fdSrc != -1) {
        close(fdSrc);
    }
    if (fdDst != -1) {
        close(fdDst);
    }
    return true;
}

std::string LocalFileSystem::AppendSlash(const std::string& src)
{
    if (src.empty()) {
        return "/";
    }
    if (src[src.length() - 1] == '/') {
        return src;
    }
    return src + '/';
}

bool LocalFileSystem::IsFileExist(const std::string& filePath)
{
    return access(filePath.c_str(), F_OK) == 0;
}

bool LocalFileSystem::CreateDirectory(const std::string& path)
{
    if (path.empty()) {
        return false;
    }
    struct stat s;
    if (lstat(path.c_str(), &s) == 0) {
        // directory exists
        return true;
    }
    return mkdir(path.c_str(), 0777) == 0;
}

} // namespace common
