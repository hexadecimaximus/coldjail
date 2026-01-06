#define _GNU_SOURCE
#include <sched.h>      // CLONE_* flags
#include <unistd.h>     // unshare, fork, getuid
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // getenv, atoi
#include <string.h>     // strcmp
#include <sys/wait.h>   // waitpid, WEXITSTATUS
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/mount.h>

int setup_namespaces(int net_none) {
    int flags = CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUTS;

    if (net_none) {
        flags |= CLONE_NEWNET;
          printf("[*] Network namespace isolated (CLONE_NEWNET)\n");
    }

    if (unshare(flags) == -1) {
          perror("[-] Failed to unshare");
        return 1;
    }

    if (mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1) {
          perror("[-] Failed to make mounts private");
        return 1;
    }

    // second fork so grandchild becomes PID 1
    pid_t init = fork();
    if (init < 0) {
          perror("[-] Failed to fork init");
        return 1;
    }
    if (init > 0) {
        int status;
        waitpid(init, &status, 0);
        _exit(WEXITSTATUS(status));
    }

    return 0;
}

