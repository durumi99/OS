#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(rest,int,x,int,y,int *,to_user){
	int res =x%y;
	put_user(res,to_user);
	return res;
}
