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
    int fdTwo[2];
    pid_t childpid;

    pipe(fdTwo);
    if ((childpid = fork()) == 0) { /* Child code: Runs ls */

        dup2(fdTwo[INP], STDOUT_FILENO);
        close(fdTwo[OUTP]);
        close(fdTwo[INP]);

        execl("/usr/bin/sort", "sort", "-k", "+1", NULL);
        perror("The exec of sort failed");
    }

    else { /* Parent code: Runs sort */
        dup2(fdTwo[OUTP], STDIN_FILENO);
        execl("/usr/bin/head", "head", "-2", NULL);
    }

    exit(0);
}
