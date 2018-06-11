// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_NODEMANAGER_ABSTRACT_LAUNCHER_H
#define FRAMEWORK_NODEMANAGER_ABSTRACT_LAUNCHER_H

#include <string>
#include <vector>

namespace framework {

class AbstractLauncher
{
public:
    virtual ~AbstractLauncher() {}
    virtual int Launch(
            const std::string& entrance,
            const std::vector<std::string>& parameters) = 0;
};

} // namespace framework
#endif // FRAMEWORK_NODEMANAGER_ABSTRACT_LAUNCHER_H
