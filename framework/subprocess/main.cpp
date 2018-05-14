// Copyright (c) 2018, DAI

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <iostream>
#include "framework/subprocess/binary_subprocess.h"

using namespace framework;

// TODO(dai): make the following two functions shareable
void ErrSys(const char* msg)
{
    perror(msg);
    exit(1);
}

void Daemonize(const char* cmd)
{
    // clear file creation mask
    umask(0);

    // first fork to become a session leader to lose controlling TTY
    pid_t pid = 0;
    if ((pid=fork()) < 0) {
        ErrSys("can't fork for the first-time");
    } else if (pid > 0) {
        ::exit(0);
    }

    // set session id
    setsid();

    // ensure future opens won't allocate controlling TTY
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        ErrSys("can't catch SIGHUP");
    }

    // second fork
    if ((pid=fork()) < 0) {
        ErrSys("can't fork for the second-time");
    } else if (pid > 0) {
        ::exit(0);
    }

    // change current working directory to root so we
    // won't prevent file systems from being unmounted
    if (chdir("/") < 0) {
        ErrSys("can't chdir to root /");
    }

    // get maximum number of file descriptors
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        ErrSys("can't get getrlimit ");
    }
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }

    // close all open file discriptor
    for (int i = 0; i < rl.rlim_max; ++i) {
        ::close(i);
    }

    // attach file descriptors 0, 1 and 2 to /dev/null
    int fd0, fd1, fd2;
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(fd0);
    fd2 = dup(fd0);

    // initialize log file
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected fds: %d, %d, %d", fd0, fd1, fd2);
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Welcome to supervisor" << std::endl;
    if (argc < 3) {
        ErrSys("inefficient parameters");
    }
    std::string supervisorAddress(argv[1]);
    std::string workingDirectory(argv[2]);
    // Daemonize("subprocess");
    return 0;
}
