// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_COMMON_ABSTRACT_PROCESS_DESCRIPTOR_H
#define FRAMEWORK_COMMON_ABSTRACT_PROCESS_DESCRIPTOR_H

#include <time.h>
#include <sys/time.h>
#include <string>
#include "framework/subprocess/abstract_subprocess.h"
#include "uuid/uuid.h"

namespace framework {

class AbstractProcessDescriptor
{
public:
    virtual ~AbstractProcessDescriptor() {}
    virtual std::string GetProcessId() = 0;
    virtual int64_t GetLastHeartbeatTimestampInMs() = 0;
    virtual void SetLastHeartbeatTimestampInMs(int64_t timestamp) = 0;
};

class BinarySubprocessDescriptor : public AbstractProcessDescriptor
{
public:
    BinarySubprocessDescriptor()
    {
        ::uuid_generate(reinterpret_cast<unsigned char*>(mUUID));
        mProcessId = kBinarySubprocessPrefix + std::string(mUUID);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        mLastHeartbeatTimestamp =
            int64_t(tv.tv_sec) * 1000 +
            int64_t(tv.tv_usec) / 1000;
    }

    std::string GetProcessId()
    {
        return mProcessId;
    }

    void SetLastHeartbeatTimestampInMs(int64_t timestamp)
    {
        mLastHeartbeatTimestamp = timestamp;
    }

    int64_t GetLastHeartbeatTimestampInMs()
    {
        return mLastHeartbeatTimestamp;
    }

private:
    const char* kBinarySubprocessPrefix = "binary_";
    char mUUID[16];
    std::string mProcessId;
    int64_t mLastHeartbeatTimestamp;
};


} // namespace framework
#endif // FRAMEWORK_COMMON_ABSTRACT_PROCESS_DESCRIPTOR_H
