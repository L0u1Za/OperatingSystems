#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
  
    for(int i = 0; i < argc; ++i) {
		printf("argv[%d] = %s\n", i, argv[i]);
    }
    for(int i = 0; envp[i] != 0; ++i) {
		printf("envp[%d] = %s\n", i, envp[i]);
    }

}
