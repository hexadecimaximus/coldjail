#include <stdio.h>
#include <unistd.h>

int exec_shell(void) {
    char *args[] = {"/bin/sh", "-i", NULL};
    char *envp[] = {
        "PATH=/bin:/sbin:/usr/bin:/usr/sbin",
        "TERM=xterm",
        "PS1=[Coldjail] \\$ ",
        NULL
    };
    
    printf("\nColdjail - Security by default, simplicity by design\nPress CTRL + D to exit\n");
    execve("/bin/sh", args, envp);
    perror("[-] Failed to exec shell");
    return 1;
}

