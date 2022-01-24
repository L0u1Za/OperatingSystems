#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    printf("Program started by:\n");
    printf ("User ID = %d\n",getuid());
    printf ("Group ID = %d\n\n",getgid());
    
    return 0;
}
