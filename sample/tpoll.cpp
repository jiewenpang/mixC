#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /*文件控制*/
#include <sys/select.h>
#include <sys/time.h> /*时间方面的函数*/
#include <errno.h> /*有关错误方面的宏*/
#include<sys/poll.h> //poll()
#include<fcntl.h>
#include<string.h> //memset()

int main(void)
{
	int fd,key_value,ret;
	struct pollfd event; //创建一个struct pollfd结构体变量，存放文件描述符、要等待发生的事件
	fd=open("/home/pjw/cdr/sql",O_RDWR); 
	if(fd<0){
		perror("open error!\n");
		exit(1);
	}
	printf("open sucessfully!\n");
	while(1){ //poll结束后struct pollfd结构体变量的内容被全部清零，需要再次设置
		memset(&event,0,sizeof(event)); //memst函数对对象的内容设置为同一值
		event.fd=fd; //存放打开的文件描述符
		event.events=POLLIN; //存放要等待发生的事件
		ret=poll((struct pollfd *)&event,1,5000); //监测event，一个对象，等待5000毫秒后超时,-1为无限等待

		//判断poll的返回值，负数是出错，0是设定的时间超时，整数表示等待的时间发生
		if(ret<0){
			printf("poll error!\n");
			exit(1);
		}
		if(ret==0){
			printf("Time out!\n");
			continue;
		}
		if(event.revents&POLLERR){ //revents是由内核记录的实际发生的事件，events是进程等待的事件
			printf("Device error!\n");
			exit(1);
		}
		if(event.revents&POLLIN){
			read(fd,&key_value,sizeof(key_value));
			printf("Key value is '%d'\n",key_value);
		}
	}
	close(fd);
	return 0;
}
