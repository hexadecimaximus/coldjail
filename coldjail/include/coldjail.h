#ifndef COLDJAIL_H
#define COLDJAIL_H

#include <sys/types.h>

// namespaces
int setup_namespaces(int net_none);

// mounts
int setup_mounts(const char *rootfs);

// devices
int setup_devices(void);

// hostname
int setup_hostname(const char *hostname);

// exec
int exec_shell(void);

// jail
int run_jail(const char *rootfs, int net_none);

#endif

