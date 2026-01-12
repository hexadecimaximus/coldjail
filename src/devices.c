/*
 * Coldjail - Minimalist Linux sandbox
 * Copyright (c) 2026 Rodrigo de Freitas
 *
 * SPDX-License-Identifier: MIT
 */

#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdio.h>
#include "coldjail.h"

int setup_devices_impl(ColdJail *cj) {
    (void) cj;
    struct stat st;
    if (stat("/dev/null", &st) == -1) {
        if (mknod("/dev/null", S_IFCHR | 0666, makedev(1, 3)) == -1)
            perror("[-] create /dev/null");
    }
    if (stat("/dev/zero", &st) == -1) {
        if (mknod("/dev/zero", S_IFCHR | 0666, makedev(1, 5)) == -1)
            perror("[-] create /dev/zero");
    }
    return 0;
}
