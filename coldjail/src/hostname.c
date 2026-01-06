#include <stdio.h>
#include <unistd.h>
#include <string.h>

int setup_hostname(const char *hostname) {
    size_t len = strlen(hostname);
    if (sethostname(hostname, len) == -1) {
        perror("[-] Falha sethostname");
        return 1;
    }
    
    return 0;
}

