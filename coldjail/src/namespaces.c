/*
 * Coldjail - Minimalist Linux sandbox
 * Copyright (c) 2026 Rodrigo de Freitas
 *
 * SPDX-License-Identifier: MIT
 */

#define _GNU_SOURCE
#include <sched.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "coldjail.h"

int setup_namespaces_impl(ColdJail *cj) {
    int flags = CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUTS;
    if (coldjail_get_net_none(cj)) {
        flags |= CLONE_NEWNET;
        printf("[*] Network namespace isolated (CLONE_NEWNET)\n");
    }

    if (unshare(flags) == -1) {
        perror("[-] unshare");
        return 1;
    }

    if (mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1) {
        perror("[-] mount private");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("[-] fork");
        return 1;
    }

    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        _exit(WEXITSTATUS(status));
    }

    return 0;
}
