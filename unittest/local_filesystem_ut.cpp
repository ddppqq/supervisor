// Copyright (c) 2018, DAI

#include "framework/common/local_filesystem.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "unittest/util.h"

using namespace common;
using namespace ::testing;

class LocalFileSystemTest : public LocalFileSystem
{
public:
    LocalFileSystemTest()
    {
        mFileSystem = new LocalFileSystem();
    }

    ~LocalFileSystemTest()
    {
        delete mFileSystem;
    }

    bool Copy(const std::string& src, const std::string& dst)
    {
        return mFileSystem->Copy(src, dst);
    }

    std::string GetFileName(const std::string& path)
    {
        return mFileSystem->GetFileName(path);
    }

    std::string GetPathName(const std::string& path)
    {
        return mFileSystem->GetPathName(path);
    }

    bool IsFile(const std::string& path)
    {
        return mFileSystem->IsFile(path);
    }

    bool CopyFile(const std::string& src, const std::string& dst)
    {
        return this->LocalFileSystem::CopyFile(src, dst);
    }

    std::string AppendSlash(const std::string& src)
    {
        return this->LocalFileSystem::AppendSlash(src);
    }

    bool IsFileExist(const std::string& filePath)
    {
        return mFileSystem->IsFileExist(filePath);
    }

    bool CreateDirectory(const std::string& path)
    {
        return mFileSystem->CreateDirectory(path);
    }

private:
    LocalFileSystem* mFileSystem;
};

TEST(LocalFileSystemTest, Copy)
{
    LocalFileSystemTest t;

    // copy empty file
    EXPECT_FALSE(t.Copy("", "non/exist/directory/"));

    // copy non-exist file
    EXPECT_FALSE(t.Copy("./abc", "./def"));

    // create a temporary file
    EXPECT_TRUE(CreateFile("./abc"));

    // copy file + change file name
    EXPECT_TRUE(t.Copy("./abc", "./def"));
    EXPECT_TRUE(t.IsFileExist("./def"));
    EXPECT_TRUE(Delete("./abc"));
    EXPECT_TRUE(Delete("./def"));

    // copy file + mixed directory
    EXPECT_TRUE(t.CreateDirectory("./abc"));
    EXPECT_TRUE(t.CreateDirectory("./abc/def"));
    EXPECT_TRUE(CreateFile("./abc/aaa"));
    EXPECT_TRUE(CreateFile("./abc/def/bbb"));
    EXPECT_TRUE(CreateFile("./abc/def/ccc"));
    EXPECT_TRUE(t.CreateDirectory("cba"));
    EXPECT_TRUE(t.Copy("./abc/", "./cba/"));
    EXPECT_TRUE(t.IsFileExist("./cba/aaa"));
    EXPECT_TRUE(t.IsFileExist("./cba/def/bbb"));
    EXPECT_TRUE(t.IsFileExist("./cba/def/ccc"));

    // clean up
    EXPECT_TRUE(Delete("./abc/aaa"));
    EXPECT_TRUE(Delete("./abc/def/bbb"));
    EXPECT_TRUE(Delete("./abc/def/ccc"));
    EXPECT_TRUE(Delete("./abc/def/"));
    EXPECT_TRUE(Delete("./cba/aaa"));
    EXPECT_TRUE(Delete("./cba/def/bbb"));
    EXPECT_TRUE(Delete("./cba/def/ccc"));
    EXPECT_TRUE(Delete("./cba/def/"));
    EXPECT_TRUE(Delete("./abc/"));
    EXPECT_TRUE(Delete("./cba/"));

    // dst directory doesn't exist
    EXPECT_TRUE(t.CreateDirectory("./abc"));
    EXPECT_TRUE(CreateFile("./abc/aaa"));
    EXPECT_TRUE(t.Copy("./abc/", "./cba/"));
    EXPECT_TRUE(t.IsFileExist("./cba/aaa"));

    // clean up
    EXPECT_TRUE(Delete("./abc/aaa"));
    EXPECT_TRUE(Delete("./cba/aaa"));
    EXPECT_TRUE(Delete("./abc/"));
    EXPECT_TRUE(Delete("./cba/"));
}

TEST(LocalFileSystemTest, GetFileName)
{
    LocalFileSystemTest t;
    EXPECT_EQ(t.GetFileName(""), "");
    EXPECT_EQ(t.GetFileName("/"), "");
    EXPECT_TRUE(t.CreateDirectory("./abc/"));
    EXPECT_TRUE(CreateFile("./abc/def"));
    EXPECT_EQ(t.GetFileName("./abc/def"), "def");
    EXPECT_TRUE(Delete("./abc/def"));
    EXPECT_EQ(t.GetFileName("./abc/"), "");
    EXPECT_TRUE(Delete("./abc/"));
}

TEST(LocalFileSystemTest, GetPathName)
{
    LocalFileSystemTest t;
    EXPECT_EQ(t.GetPathName(""), "");
    EXPECT_EQ(t.GetPathName("/"), "/");
    EXPECT_TRUE(t.CreateDirectory("./abc/"));
    EXPECT_TRUE(CreateFile("./abc/def"));
    EXPECT_EQ(t.GetPathName("./abc/def"), "./abc/");
    EXPECT_EQ(t.GetPathName("./abc/"), "./abc/");
    EXPECT_TRUE(Delete("./abc/def"));
    EXPECT_TRUE(Delete("./abc/"));
}

TEST(LocalFileSystemTest, IsFile)
{
    LocalFileSystemTest t;
    EXPECT_FALSE(t.IsFile(""));

    EXPECT_TRUE(CreateFile("abc"));
    EXPECT_TRUE(t.IsFile("abc"));
    EXPECT_TRUE(Delete("abc"));

    EXPECT_TRUE(t.CreateDirectory("abc"));
    EXPECT_FALSE(t.IsFile("abc"));
    EXPECT_TRUE(Delete("abc"));
}

TEST(LocalFileSystemTest, CopyFile)
{
    LocalFileSystemTest t;

    // copy empty file
    EXPECT_FALSE(t.CopyFile("", "non/exist/directory/"));

    // copy non-exist file
    EXPECT_FALSE(t.CopyFile("./abc", "non/exist/directory/"));

    // create a temporary file
    EXPECT_TRUE(CreateFile("./abc"));

    // copy and rename file to local directory
    EXPECT_TRUE(t.CopyFile("./abc", "./def"));
    EXPECT_TRUE(t.IsFileExist("./def"));
    EXPECT_TRUE(Delete("./abc"));
    EXPECT_TRUE(Delete("./def"));

    // same file name
    EXPECT_TRUE(t.CreateDirectory("./abc/"));
    EXPECT_TRUE(CreateFile("./abc/def"));
    EXPECT_TRUE(t.CopyFile("./abc/def", "./"));
    EXPECT_TRUE(t.IsFileExist("./def"));
    EXPECT_TRUE(Delete("./def"));
    EXPECT_TRUE(Delete("./abc/def"));
    EXPECT_TRUE(Delete("./abc/"));
}

TEST(LocalFileSystemTest, AppendSlash)
{
    LocalFileSystemTest t;
    EXPECT_EQ(t.AppendSlash(""), "/");
    EXPECT_EQ(t.AppendSlash("abc"), "abc/");
    EXPECT_EQ(t.AppendSlash("/abc"), "/abc/");
    EXPECT_EQ(t.AppendSlash("abc/ab"), "abc/ab/");
}

TEST(LocalFileSystemTest, IsFileExist)
{
    LocalFileSystemTest t;
    EXPECT_FALSE(t.IsFileExist(""));

    EXPECT_TRUE(CreateFile("abc"));
    EXPECT_TRUE(t.IsFileExist("abc"));

    EXPECT_TRUE(Delete("abc"));
    EXPECT_FALSE(t.IsFileExist("abc"));
}

TEST(LocalFileSystemTest, CreateDirectory)
{
    LocalFileSystemTest t;
    EXPECT_FALSE(t.CreateDirectory(""));

    EXPECT_TRUE(t.CreateDirectory("./abc"));

    EXPECT_TRUE(Delete("./abc"));
}
