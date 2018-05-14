// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUBPROCESS_ABSTRACT_SUBPROCESS_H
#define FRAMEWORK_SUBPROCESS_ABSTRACT_SUBPROCESS_H

#include <string>
#include "protocol/common.pb.h"

namespace framework {

class AbstractSubprocess
{
public:
    virtual ~AbstractSubprocess() {}
    virtual ProcessInfo Start() = 0;
    virtual int Stop() = 0;
    virtual ProcessInfo GetProcessInfo() = 0;
};

} // namespace framework
#endif // FRAMEWORK_SUBPROCESS_ABSTRACT_SUBPROCESS_H
