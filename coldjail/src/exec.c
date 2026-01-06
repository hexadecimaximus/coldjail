#include <stdio.h>
#include <unistd.h>

int exec_shell(void) {
    char *args[] = {"/bin/sh", NULL};
    char *envp[] = {
        "PATH=/bin:/sbin:/usr/bin:/usr/sbin",
        "TERM=xterm",
        "PS1=[Coldjail] \\$ ",
        NULL
    };
    
    printf("\nColdjail - Segurança por padrão, simplicidade por design\nPressione CTRL + D para sair\n");
    execve("/bin/sh", args, envp);
    perror("[-] Falha exec shell");
    return 1;
}

