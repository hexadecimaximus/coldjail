/*
 * Coldjail - Minimalist Linux sandbox
 * Copyright (c) 2026 Rodrigo de Freitas
 *
 * SPDX-License-Identifier: MIT
 */

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "coldjail.h"

static int do_pivot_root(const char *new_root, const char *put_old) {
    return syscall(SYS_pivot_root, new_root, put_old);
}

int setup_mounts_impl(ColdJail *cj) {
    const char *rootfs = coldjail_get_rootfs(cj);

    if (mount(rootfs, rootfs, NULL, MS_BIND | MS_REC, NULL) == -1) {
        perror("[-] bind mount rootfs");
        return 1;
    }

    if (chdir(rootfs) == -1) {
        perror("[-] chdir rootfs");
        return 1;
    }

    mkdir("old_root", 0700);

    if (do_pivot_root(".", "old_root") == -1) {
        perror("[-] pivot_root");
        return 1;
    }

    chdir("/");

    // Montagens virtuais
    mount(NULL, "/proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
    mount(NULL, "/sys", "sysfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
    mount(NULL, "/tmp", "tmpfs", MS_NOSUID | MS_NODEV, NULL);

    // /dev
    mkdir("/dev", 0755);
    mount(NULL, "/dev", "devtmpfs", MS_NOSUID | MS_STRICTATIME, NULL);

    mkdir("/dev/pts", 0755);
    mount(NULL, "/dev/pts", "devpts", MS_NOSUID | MS_NOEXEC, NULL);

    // Limpeza
    if (umount2("/old_root", MNT_DETACH) == 0) {
        rmdir("/old_root");
    }

    return 0;
}
