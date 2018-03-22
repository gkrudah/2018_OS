#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	char *buf = "Hello";
	int ret_val;
	ret_val = myfunction(buf);
	printf(1, "Return value : 0x%x\n", ret_val);
	exit();
	
	return 0;
}
