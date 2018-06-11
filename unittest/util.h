// Copyright (c) 2018, DAI

#ifndef UNITTEST_UTIL_H
#define UNITTEST_UTIL_H

#include <fcntl.h>
#include <iostream>
#include <string>

bool CreateFile(const std::string& filePath)
{
    if (access(filePath.c_str(), F_OK) == 0) {
        return false;
    }
    int fd = -1;
    if ((fd = open(
        filePath.c_str(),
        O_CREAT | O_TRUNC | O_RDWR,
        S_IRWXU)) == -1) {
        std::cout << strerror(errno) << std::endl;
        return false;
    }
    close(fd);
    return true;
}

bool Delete(const std::string& filePath)
{
    return remove(filePath.c_str()) == 0;
}

#endif // UNITTEST_UTIL_H
