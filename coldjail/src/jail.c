#include <stdio.h>
#include <stdlib.h>
#include "coldjail.h"

int run_jail(const char *rootfs, int net_none) {
    if (setup_namespaces(net_none) != 0) return 1;
    if (setup_mounts(rootfs) != 0) return 1;
    if (setup_devices() != 0) return 1;
    if (setup_hostname("coldjail") != 0) return 1;
    if (exec_shell() != 0) return 1;
    return 0;
}

