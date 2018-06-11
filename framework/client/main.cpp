// Copyright (c) 2018, DAI

#include <unistd.h>
#include <iostream>
#include "framework/client/client.h"
#include "protocol/common.pb.h"

using namespace framework;

extern int optind, opterr, optopt;
extern char* optarg;

namespace {
const int kAllParameterSet = 0b1111;
const int kConnectionInfo = 0b0001;
const int kEntrance = 0b0010;
const int kSrcLocation = 0b0100;
const int kDstLocation = 0b1000;
const char* kUsage =
    "==============================================================\n"
    "./client -c localhost:50051 -e entranceName -s /path/to/src/location/ -d /path/to/dst/location/ -> connect server through localhost:50051 and start subprocess based on info provided \n" // NOLINT
    "./client -l localhost:50051 -> list all subprocesses \n"
    "./client -p localhost:50051 -> echo server interface \n"
    "./client -h -> help\n"
    "==============================================================\n";
} // anonymous namespace

void PrintUsageAndExit()
{
    std::cout << kUsage << std::flush;
    exit(-1);
}

int main(int argc, char* argv[])
{
    ResourceInfo info;
    std::string serviceIPPort;
    int p = -1;
    int allParameters = 0;
    bool isSpecifyP = false;
    bool isSpecifyL = false;
    while ((p = ::getopt(argc, argv, "c:e:s:d:p:l:h")) != -1) {
        switch (p) {
            case 'c':
                serviceIPPort = std::string(optarg);
                allParameters |= kConnectionInfo;
                break;
            case 'e':
                info.set_entrance(optarg);
                allParameters |= kEntrance;
                break;
            case 's':
                info.set_srclocation(optarg);
                allParameters |= kSrcLocation;
                break;
            case 'd':
                info.set_dstlocation(optarg);
                allParameters |= kDstLocation;
                break;
            case 'p':
                serviceIPPort = std::string(optarg);
                isSpecifyP = true;
                break;
            case 'l':
                isSpecifyL = true;
                serviceIPPort = std::string(optarg);
                break;
            case 'h':
            default:
                PrintUsageAndExit();
        }
    }

    // validate parameters
    if (argc == 1) {
        PrintUsageAndExit();
    }
    if ((isSpecifyP && allParameters) || (isSpecifyP && argc > 3)) {
        PrintUsageAndExit();
    }
    if (allParameters && allParameters != kAllParameterSet) {
        PrintUsageAndExit();
    }
    if (isSpecifyL && argc != 3) {
        PrintUsageAndExit();
    }

    std::unique_ptr<AbstractClient> client(
            new Client(::grpc::CreateChannel(serviceIPPort, ::grpc::InsecureChannelCredentials()))); // NOLINT
    if (isSpecifyP) {
        std::string msg = client->Ping("hi this is client");
        std::cout << "-p sprcified, responed message is :" + msg << std::endl;
    } else if (isSpecifyL) {
        std::cout << "-l sprcified" << std::endl;
        std::vector<ProcessInfo> infos;
        if (client->ListProcesses("", &infos).ok()) {
            if (infos.empty()) {
                std::cout << "no process is running" << std::endl;
            }
            for (auto i : infos) {
                std::cout << "process id is: " << i.processid() << std::endl;
            }
        } else {
            std::cout << "ListProcesses failed" << std::endl;
        }
    } else {
        std::cout << "-c sprcified" << std::endl;
        if (client->Start(info).ok()) {
            std::cout << "start process ok" << std::endl;
        }
    }
    return 0;
}
