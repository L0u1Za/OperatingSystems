#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid = fork();

    if (pid == -1) {
        printf ("Error.\n");
    } else if (pid == 0) {
        printf ("Child (PID=%d)\n", getpid());
        printf ("I'm executing cat for task1.c\n");
        (void) execle("/bin/cat","/bin/cat","task1.c", 0, envp);
    } else {
        printf ("Parent (PID=%d, child's PID=%d)\n", getpid(), pid);
    }

}
