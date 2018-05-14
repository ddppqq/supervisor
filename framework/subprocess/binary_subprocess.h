// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUBPROCESS_BINARY_SUBPROCESS_H
#define FRAMEWORK_SUBPROCESS_BINARY_SUBPROCESS_H

#include <string>
#include "framework/common/abstract_process_descriptor.h"
#include "framework/common/local_filesystem.h"
#include "protocol/common.pb.h"
#include "uuid/uuid.h"

namespace framework {

class BinarySubprocessDescriptor : public AbstractProcessDescriptor
{
public:
    BinarySubprocessDescriptor()
    {
        ::uuid_generate(reinterpret_cast<unsigned char*>(mUUID));
        mProcessId = kBinarySubprocessPrefix + std::string(mUUID);
    }

    std::string GetProcessId()
    {
        return mProcessId;
    }

    AbstractSubprocess* GetService()
    {
        return NULL;
    }

private:
    const char* kBinarySubprocessPrefix = "binary_";
    char mUUID[16];
    std::string mProcessId;
};

class BinarySubprocess : public AbstractSubprocess
{
public:
    BinarySubprocess();
    ~BinarySubprocess();
    ProcessInfo Start();
    int Stop();
    ProcessInfo GetProcessInfo();

private:
    AbstractProcessDescriptor* mDescriptor;
};

} // namespace framework
#endif // FRAMEWORK_SUBPROCESS_BINARY_SUBPROCESS_H
