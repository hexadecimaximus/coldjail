#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>
#include <sys/syscall.h>
#include <sys/stat.h>

static int do_pivot_root(const char *new_root, const char *put_old) {
    return syscall(SYS_pivot_root, new_root, put_old);
}

int setup_mounts(const char *rootfs) {
    if (mount(rootfs, rootfs, NULL, MS_BIND | MS_REC, NULL) == -1) {
          perror("[-] Failed to bind-mount rootfs");
        return 1;
    }

    if (chdir(rootfs) == -1) {
          perror("[-] Failed to chdir into rootfs");
        return 1;
    }

    mkdir("old_root", 0700);

    if (do_pivot_root(".", "old_root") == -1) {
          perror("[-] Failed to pivot_root");
        return 1;
    }

    chdir("/");

    mount(NULL, "/proc", "proc", 0, NULL);
    mount(NULL, "/sys", "sysfs", 0, NULL);
    mount(NULL, "/tmp", "tmpfs", 0, NULL);

    mkdir("/dev", 0755);
    mount(NULL, "/dev", "devtmpfs", 0, NULL);

    mkdir("/dev/pts", 0755);
    mount(NULL, "/dev/pts", "devpts", 0, NULL);

    if (umount2("/old_root", MNT_DETACH) == -1) {
         perror("[-] Failed to unmount old_root");
    }
    rmdir("/old_root");

    return 0;
}

