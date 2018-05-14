// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_COMMON_ABSTRACT_PROCESS_DESCRIPTOR_H
#define FRAMEWORK_COMMON_ABSTRACT_PROCESS_DESCRIPTOR_H

#include <string>
#include "framework/subprocess/abstract_subprocess.h"

namespace framework {

class AbstractProcessDescriptor
{
public:
    virtual ~AbstractProcessDescriptor() {}
    virtual std::string GetProcessId() = 0;
    virtual AbstractSubprocess* GetService() = 0;
};

} // namespace framework
#endif // FRAMEWORK_COMMON_ABSTRACT_PROCESS_DESCRIPTOR_H
