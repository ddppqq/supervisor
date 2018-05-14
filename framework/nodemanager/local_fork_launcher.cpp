// Copyright (c) 2018, DAI

#include "framework/nodemanager/local_fork_launcher.h"

#include <unistd.h>
#include <iostream>

namespace framework {

bool LocalForkLauncher::Launch(
        const std::string& entrance,
        const std::vector<std::string>& parameters)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        std::cout << strerror(errno) << std::endl;
        exit(-1);
    } else if (pid == 0) {
    }
    return true;
}

} // namespace framework
