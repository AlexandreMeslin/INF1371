#include <stdio.h>
#include <sys/ipc.h>

int main(void)
{
	printf("IPC_CREAT: %d\nIPC_EXCL: %d\nIPC_NOWAIT: %d\n", IPC_CREAT, IPC_EXCL, IPC_NOWAIT);
	return 0;
}
