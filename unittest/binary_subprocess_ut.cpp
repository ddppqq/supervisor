// Copyright (c) 2018, DAI

#include "framework/subprocess/binary_subprocess.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace common;
using namespace framework;
using namespace ::testing;
using namespace ::google::protobuf;

TEST(BinarySubprocessDescriptor, GetProcessId)
{
    BinarySubprocessDescriptor descriptor1;
    BinarySubprocessDescriptor descriptor2;
    EXPECT_TRUE(descriptor1.GetProcessId() != descriptor2.GetProcessId());
    EXPECT_TRUE(
            descriptor1.GetProcessId().find("binary_") != std::string::npos);
    EXPECT_TRUE(
            descriptor2.GetProcessId().find("binary_") != std::string::npos);
}
