#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    
    if (pid == -1) {
        printf ("Error.\n");
    } else if (pid == 0) {
        printf ("Child (PID=%d)\n", getpid());
    } else {
        printf ("Parent (PID=%d, child's PID=%d)\n", getpid(), pid);
    }
    
    return 0;
}