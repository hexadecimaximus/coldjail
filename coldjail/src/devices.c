#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>

int setup_devices(void) {
    struct stat st;
    if (stat("/dev/null", &st) == -1) {
        if (mknod("/dev/null", S_IFCHR | 0666, makedev(1,3)) == -1)
            perror("[-] Failed to create /dev/null");
    }
    if (stat("/dev/zero", &st) == -1) {
        if (mknod("/dev/zero", S_IFCHR | 0666, makedev(1,5)) == -1)
            perror("[-] Failed to create /dev/zero");
    }
    return 0;
}

