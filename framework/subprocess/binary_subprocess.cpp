// Copyright (c) 2018, DAI

#include "framework/subprocess/binary_subprocess.h"

namespace framework {

BinarySubprocess::BinarySubprocess()
{
    mDescriptor = new BinarySubprocessDescriptor();
}

BinarySubprocess::~BinarySubprocess()
{
    delete mDescriptor;
}

ProcessInfo BinarySubprocess::Start()
{
    return ProcessInfo();
}

int BinarySubprocess::Stop()
{
    return 0;
}

ProcessInfo BinarySubprocess::GetProcessInfo()
{
    return ProcessInfo();
}

} // namespace framework
