// Copyright (c) 2018, DAI

#include "framework/nodemanager/local_fork_launcher.h"

#include <unistd.h>
#include <iostream>
#include "framework/common/local_filesystem.h"

namespace framework {

int LocalForkLauncher::Launch(
        const std::string& entrance,
        const std::vector<std::string>& parameters)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        std::cout << strerror(errno) << std::endl;
        exit(-1);
    } else if (pid == 0) {
        common::LocalFileSystem fs;
        std::string path = fs.GetPathName(entrance);
        if (chdir(path.c_str()) != 0) {
            std::cout << strerror(errno) << std::endl;
            exit(-1);
        }
        std::unique_ptr<char*> p(GetParameterList(parameters));
        execv(entrance.c_str(), p.get());
    }
    return 0;
}

char** LocalForkLauncher::GetParameterList(
        const std::vector<std::string>& parameters)
{
    if (parameters.empty()) {
        return NULL;
    }
    char** p = NULL;
    if (!parameters.empty()) {
        p = new char*[parameters.size()];
        for (int i = 0; i < parameters.size(); ++i) {
            p[i] = const_cast<char*>(parameters[i].c_str()); // NOLINT
        }
    }
    return p;
}

} // namespace framework
