/*
 * Coldjail - Minimalist Linux sandbox
 * Copyright (c) 2026 Rodrigo de Freitas
 *
 * SPDX-License-Identifier: MIT
 */

#include "coldjail.h"
#include <stdlib.h>
#include <string.h>


struct coldjail {
    //private data
    char *rootfs;
    const char *hostname;
    int net_none;  // 1 = isolated (default)
};

// Forward declarations of modules
int setup_namespaces_impl(ColdJail *cj);
int setup_mounts_impl(ColdJail *cj);
int setup_devices_impl(ColdJail *cj);
int setup_hostname_impl(ColdJail *cj);
int exec_shell_impl(ColdJail *cj);

ColdJail *coldjail_new(const char *rootfs) {
    ColdJail *cj = calloc(1, sizeof(ColdJail));
    if (!cj) return NULL;
    cj->rootfs = strdup(rootfs);
    cj->hostname = "coldjail";
    cj->net_none = 1;  // secure by default
    return cj;
}

void coldjail_free(ColdJail *cj) {
    if (cj) {
        free(cj->rootfs);
        free(cj);
    }
}

void coldjail_set_net_none(ColdJail *cj, int enabled) {
    cj->net_none = enabled;
}

const char *coldjail_get_hostname(const ColdJail *cj) {
    return cj->hostname;
}

const char *coldjail_get_rootfs(const ColdJail *cj) {
    return cj->rootfs;
}

int coldjail_run(ColdJail *cj) {
    if (setup_namespaces_impl(cj) != 0) return 1;
    if (setup_mounts_impl(cj) != 0) return 1;
    if (setup_devices_impl(cj) != 0) return 1;
    if (setup_hostname_impl(cj) != 0) return 1;
    if (exec_shell_impl(cj) != 0) return 1;
    return 0;
}
