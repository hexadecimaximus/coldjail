#include <stdio.h>
#include <string.h>
#include "coldjail.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: sudo %s <rootfs> [--net=none]\n", argv[0]);
        return 1;
    }

    const char *rootfs = NULL;
    int net_none = 0;

    // Scan all arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--net=none") == 0) {
            net_none = 1;
        } else if (argv[i][0] != '-') {
            if (rootfs) {
                fprintf(stderr, "Error: multiple rootfs paths provided\n");
                return 1;
            }
            rootfs = argv[i];
        }
        // Ignore unknow flags (ex: --help)
    }

    if (!rootfs) {
        fprintf(stderr, "Error: no rootfs path provided\n");
        return 1;
    }

    ColdJail *cj = coldjail_new(rootfs);
    if (!cj) {
        fprintf(stderr, "[-] Failed to initialize ColdJail\n");
        return 1;
    }

    coldjail_set_net_none(cj, net_none);
    int ret = coldjail_run(cj);
    coldjail_free(cj);
    return ret;
}
