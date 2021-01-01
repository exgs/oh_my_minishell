#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	char *data1[] = {"ps", "-e", "-f",0};
	execve("/bin/ps", data1, envp);

	return (0);
}