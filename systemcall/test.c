#include<stdio.h>
#include<unistd.h>

#define __NR_plus 442
#define __NR_minus 443
#define __NR_multi 444
#define __NR_rest 445

int main(){
	int a,b,res;
	char op;
	scanf("%d%c%d",&a,&op,&b);
	switch(op){
	case '+':
		syscall(__NR_plus,a,b,&res);
		break;
	case '-':
		syscall(__NR_minus,a,b,&res);
		break;
	case '*':
		syscall(__NR_multi,a,b,&res);
		break;
	case '%':
		syscall(__NR_rest,a,b,&res);
		break;
	default:
		break;
	}
	printf("%d %c %d = %d\n",a,op,b,res);
	return 0;	
}
