/* Title: pipedup2.c
 * Description: ENCE360 Example code - dup2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define INP 1
#define OUTP 0

int main(void) {
    int fd[2];
    pid_t childpid;

    int fdTwo[2];
    pipe(fdTwo);

    pipe(fd);
    if ((childpid = fork()) == 0) { /* Child code: Runs ls */

        pid_t grandChildPid;

        if ((grandChildPid = fork()) == 0) {
            dup2(fd[INP], STDOUT_FILENO);
            close(fd[OUTP]);
            close(fd[INP]);
            execl("/bin/ls", "ls", "-l", NULL);
            perror("The exec of ls failed");
        }
        else {
            dup2(fd[OUTP], STDIN_FILENO);
            close(fd[OUTP]);
            close(fd[INP]);

            dup2(fdTwo[INP], STDOUT_FILENO);
            close(fdTwo[OUTP]);
            close(fdTwo[INP]);
            execl("/usr/bin/sort", "sort", "-k", "+8", NULL);
            perror("The exec of sort failed");
        }
    }

    else { /* Parent code: Runs sort */
        dup2(fdTwo[OUTP], STDIN_FILENO);
        execl("/usr/bin/head", "head", "-5", NULL);

    }

    exit(0);
}