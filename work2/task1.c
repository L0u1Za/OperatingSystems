#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);
    // Для кaждого зaпускa PID увеличивaется, a PPID остaется неизменным.
    return 0;
}