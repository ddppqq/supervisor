// Copyright (c) 2018, DAI

#include <string>
#include <vector>
#include "framework/nodemanager/local_fork_launcher.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace framework;
using namespace ::testing;

class LocalForkLauncherTest : public LocalForkLauncher
{
public:
    int Launch(
            const std::string& entrance,
            const std::vector<std::string>& parameters)
    {
        // commnet out this function implementation
        return 0;
    }

    char** GetParameterList(const std::vector<std::string>& parameters)
    {
        return this->LocalForkLauncher::GetParameterList(parameters);
    }
};

TEST(LocalForkLauncher, GetParameterList)
{
    LocalForkLauncherTest launcher;
    std::vector<std::string> parameters = {"p1", "p2", "p3"};
    std::unique_ptr<char*> p(launcher.GetParameterList(parameters));
    EXPECT_EQ(std::string("p1"), std::string(p.get()[0]));
    EXPECT_EQ(std::string("p2"), std::string(p.get()[1]));
    EXPECT_EQ(std::string("p3"), std::string(p.get()[2]));
}
