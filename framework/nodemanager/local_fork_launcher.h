// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_LOCAL_FORK_LAUNCHER_H
#define FRAMEWORK_NODEMANAGER_LOCAL_FORK_LAUNCHER_H

#include <string>
#include <vector>
#include "framework/nodemanager/abstract_launcher.h"

namespace framework {

class LocalForkLauncher : public AbstractLauncher
{
public:
    virtual ~LocalForkLauncher() {}
    int Launch(
            const std::string& entrance,
            const std::vector<std::string>& parameters);

protected:
    char** GetParameterList(const std::vector<std::string>& parameters);
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_LOCAL_FORK_LAUNCHER_H
