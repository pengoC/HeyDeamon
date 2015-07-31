#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


void init_watch_demon(){
	pid_t pid;
	//产生第一个子进程，将父进程退出，子进程设置为新会话组长和进程组组长，与原环境（终端）脱离
	pid = fork();	
	printf("pid0=%d",pid);
	if (pid < 0){
		printf("fork error!\n");
		exit(1);
	}else if (pid > 0){
		//父进程退出
		exit(0);
	}else{
	
		printf("i am sub!~because pid = %d\n",pid);
		//当会话头（第一次生成的子进程）终止时，该会话中的所有进程（第二次生成的子进程）都会收到SIGHUP信号
		//使用 signal(SIGHUP,SIG_IGN); 来忽略掉这个信号
		signal(SIGHUP,SIG_IGN);

		setsid();//新创建session,使子进程成为为该会话组长和进程组组长。
		
		//创建孙子进程，孙子进程必然不是进程组长，不能创建终端，即可作为最后的守护进程
		int pid2 = fork();
		if (pid2 < 0){
			printf("fork error!\n");
			exit(1);
		}else if (pid2 > 0){//退出子进程，使进程不是组长，这样进程就不会打开控制终端
			exit(0);
		}else{//进入deamon的程序段
			printf("i am deamon !!!");
			
			//如果父进程有打开文件描述符，因为子进程继承了这些描述符，所以需关闭这些描述符

			//该进程所在的文件系统不能卸载，为防止这种情况发生，所以要改变当前系统目录
			chdir("./");//工作目录设置为当前目录

			FILE *pf = fopen("testDeamon.txt","a");
			int i = 1;
			char str[1000];
			while(1){
				sleep(1);
				time_t t; 
				time(&t);
				char str[] = "currtentTime: "
				fwrite(str,1,strlen(str),pf);
				fprintf(pf,"time:%s\n",asctime(localtime(&t)));
				fflush(pf);
			}
			fclose(pf);

			//重新设置了创建文件掩码
			umask(0);
		}
	}
}


int main(int argc, char *argv[])
{
	
	init_watch_demon();
	while(1){
		sleep(1);
//		syslog(
	}
	
	return 0;
}
