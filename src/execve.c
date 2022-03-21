#include <stdio.h>
#include <unistd.h>

int    main(void)
{
    char *cmd = "/usr/bin/env";

    char    *argVec[] = { cmd, "env", NULL};
    // char    *envVec[] = {NULL};
    // char *argVec[] = {"userscript", "arg1", "arg2", "3", NULL};
     char *envVec[] = {"CSC220=Linux", "SECRET=Study Hard", "HELLO=BYE"};

 
    printf("start of execve call %s:\n", cmd);
    printf("--------------------------------------------------\n");
    if (execve(cmd, argVec, envVec) == -1)
    {
        perror("Could not execute execve");
    }
    printf("Oops, something went wrong!");
    
    return (0);

}