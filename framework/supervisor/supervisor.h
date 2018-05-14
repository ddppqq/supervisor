// Copyright (c) 2018, DAI

#ifndef FRAMEWORK_SUPERVISOR_SUPERVISOR_H
#define FRAMEWORK_SUPERVISOR_SUPERVISOR_H

#include <string>
#include <unordered_map>
#include "framework/common/abstract_process_descriptor.h"
#include "framework/nodemanager/abstract_nodemanager.h"
#include "framework/supervisor/abstract_supervisor.h"

namespace framework {

class SupervisorServiceImpl;

class Supervisor : public AbstractSupervisor
{
public:
    Supervisor();
    virtual ~Supervisor();
    int Run();
    int Start(const ResourceInfo& resourceInfo);
    int Stop(std::string processId);
    ProcessInfo GetProcessInfo(std::string processId);

private:
    static void StartRpcServer();

private:
    std::unordered_map<std::string, AbstractProcessDescriptor*> mSubprocesses;
    AbstractNodeManager* mNodeManager;
};

} // namespace framework
#endif // FRAMEWORK_SUPERVISOR_SUPERVISOR_H
