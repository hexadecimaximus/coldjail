#include <stdio.h>
#include <string.h>
#include "coldjail.h"

int main(int argc, char *argv[]) {
    int net_none = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--net=none") == 0)
            net_none = 1;
    }

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <rootfs> [--net=none]\n", argv[0]);
        return 1;
    }

    return run_jail(argv[1], net_none);
}

