#include <unistd.h>
#include <stdio.h>
#include "coldjail.h"

int exec_shell_impl(ColdJail *cj) {
    char *args[] = {"/bin/sh", "-i", NULL};
    char *envp[] = {
        "PATH=/bin:/sbin:/usr/bin:/usr/sbin",
        "TERM=xterm",
        "PS1=[Coldjail] \\$ ",
        NULL
    };

    printf("\nColdjail - Security by default, simplicity by design\n");
    printf("Press CTRL + D to exit\n");
    execve("/bin/sh", args, envp);
    perror("[-] exec shell");
    return 1;
}
