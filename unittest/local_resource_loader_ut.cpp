// Copyright (c) 2018, DAI

#include "framework/common/local_filesystem.h"
#include "framework/nodemanager/local_resource_loader.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "protocol/common.pb.h"
#include "unittest/util.h"

using namespace common;
using namespace framework;
using namespace ::testing;
using namespace ::google::protobuf;

// src/
// ---entrancefile
// ---file1
// ---file2
// ---lib/
// ------lib1.so
// ------lib2.so
void PrepareResourceDirectory()
{
    LocalFileSystem fs;
    fs.CreateDirectory("src/");
    fs.CreateDirectory("src/lib/");
    CreateFile("src/entrancefile");
    CreateFile("src/file1");
    CreateFile("src/file2");
    CreateFile("src/lib/lib1.so");
    CreateFile("src/lib/lib2.so");
}

void CleanupResourceDirectory()
{
    Delete("src/entrancefile");
    Delete("src/file1");
    Delete("src/file2");
    Delete("src/lib/lib1.so");
    Delete("src/lib/lib2.so");
    Delete("src/lib/");
    Delete("src/");

    Delete("dst/entrancefile");
    Delete("dst/file1");
    Delete("dst/file2");
    Delete("dst/lib/lib1.so");
    Delete("dst/lib/lib2.so");
    Delete("dst/lib/");
    Delete("dst/");
}

TEST(BinaryResourceLoader, LoadResource)
{
    ResourceInfo info;
    info.set_srclocation("src/");
    info.set_dstlocation("dst/");
    info.set_entrance("entrancefile");
    info.set_resourcetype(ResourceType::BINARY);

    PrepareResourceDirectory();
    LocalFileSystem fs;
    // check src file existence
    EXPECT_TRUE(fs.IsFileExist("src/entrancefile"));
    EXPECT_TRUE(fs.IsFileExist("src/file1"));
    EXPECT_TRUE(fs.IsFileExist("src/file2"));
    EXPECT_TRUE(fs.IsFileExist("src/lib/lib1.so"));
    EXPECT_TRUE(fs.IsFileExist("src/lib/lib2.so"));
    EXPECT_TRUE(fs.IsFileExist("src/lib/"));

    // load src files to dst directory
    LocalResrouceLoader* loader = new LocalResrouceLoader();
    EXPECT_TRUE(loader->LoadResource(info));

    // check dst file existence
    EXPECT_TRUE(fs.IsFileExist("dst/entrancefile"));
    EXPECT_TRUE(fs.IsFileExist("dst/file1"));
    EXPECT_TRUE(fs.IsFileExist("dst/file2"));
    EXPECT_TRUE(fs.IsFileExist("dst/lib/lib1.so"));
    EXPECT_TRUE(fs.IsFileExist("dst/lib/lib2.so"));
    EXPECT_TRUE(fs.IsFileExist("dst/lib/"));

    delete loader;
    CleanupResourceDirectory();
}

/*
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
*/
