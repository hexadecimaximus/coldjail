#include <stdio.h>
#include <unistd.h>
#include <string.h>

int setup_hostname(const char *hostname) {
    size_t len = strlen(hostname);
    if (sethostname(hostname, len) == -1) {
        perror("[-] Fail sethostname");
        return 1;
    }
    
    return 0;
}

