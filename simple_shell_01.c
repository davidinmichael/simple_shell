#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include 'main.h'

#define MAX_LENGTH 256

int main()
{
    char *input, *command;
    char buffer[MAX_LENGTH];
    pid_t pid;
    int status;

    while (1)
    {
        printf("simple_shell> ");

        if (!fgets(buffer, MAX_LENGTH, stdin))
            break;

        buffer[strlen(buffer) - 1] = '\0';

        input = buffer;
        command = strtok(input, " ");

        pid = fork();
        if (pid == 0)
        {
            if (execve(command, NULL, NULL) == -1)
                perror("Error");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
            perror("Error");
        else
        {
            waitpid(pid, &status, WEXITSTATUS(status));
        }
    }
    return 0;
}

