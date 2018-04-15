#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	int pid;
	int i, j = 0;

	pid = fork();

	if(pid < 0)
	{	
		printf(1, "fork fail\n");
		exit();
	}
	else if(pid == 0)
	{
		for(i = 0;i < 100;i++)
		{
			printf(1, "child\n");
			yield();
		}
	}
	else
	{
		for(j = 0;j < 100;j++)
		{
			if(j == 99) wait();
			printf(1, "parent\n");
			yield();
		}
	}
	
	exit();
}
