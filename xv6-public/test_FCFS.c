#include "types.h"
#include "stat.h"
#include "user.h"
//#include "defs.h"

int main()
{
	int pid, i, j = 0;
	
	for(i = 0;i < 2;i++)
		pid = fork();

	if(pid < 0)
	{
		printf(1, "fork fail\n");
		exit();
	}
	else if(pid == 0)
	{
		for(i = 0;i < 10;i++)
			printf(1, "child progress %d\n", i);
	}
	else
	{
		for(j = 0;j < 10;j++)
			printf(1, "parent progress %d\n", j);

		wait();
	}
	exit();
}
