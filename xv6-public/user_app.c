#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	__asm__("int $128");
	
	exit();
}
