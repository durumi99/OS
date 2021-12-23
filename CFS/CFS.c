#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
	int status;
	int pid[21];
	for(int i = 0 ; i < 21 ; i++){
		if( ( pid[i] = fork() ) == 0){
			printf("%d process begins\n",getpid());
			int tmp = 1;
			for(int i = 0 ; i < 99999999; i++)
				tmp *= tmp;
			printf("%d process ends\n",getpid());
			exit(100+i);
		}
	}
	for(int i = 0 ; i < 21 ; i++) {
		pid_t wpid = waitpid(pid[i],&status,0);
		}
	printf("---------- All processes end ----------\n");
	return 0;
}
