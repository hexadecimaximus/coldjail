/*
 * Coldjail - Minimalist Linux sandbox
 * Copyright (c) 2026 Rodrigo de Freitas
 *
 * SPDX-License-Identifier: MIT
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "coldjail.h"

int setup_hostname_impl(ColdJail *cj) {
    if (sethostname(cj->hostname, strlen(cj->hostname)) == -1) {
        perror("[-] sethostname");
        return 1;
    }
    return 0;
}
