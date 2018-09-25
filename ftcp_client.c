#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<unistd.h>

#pragma pack(1)

typedef struct _file_info
{
	char name[51];
	unsigned int size;


}file_info;	
#pragma pack()

int main(int argc,char** argv )
{
	struct stat st;
	file_info fi;
	

	//第一步：创建套接字，相当于买部手机
	int sock;
	sock = socket(AF_INET,SOCK_STREAM,0);
	
	//第二步：绑定地址(可以省略)，相当于给手机上号
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(atoi(argv[1]));
	
	if(bind(sock,(struct sockaddr*)&myaddr,sizeof(myaddr)) == -1)
	{
		perror("bind error");
		exit(1);			
	}
	
	//第三步：连接服务器，相当于呼叫对方
	struct sockaddr_in srvaddr;//指定服务器地址
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	srvaddr.sin_port = htons(atoi(argv[2]));//连接服务器地址
	
	if(connect(sock,(struct sockaddr*)&srvaddr,sizeof(srvaddr)) == -1)
	{
		perror("connect error");
		exit(1);
	}
	
	//第四步：收发数据
	

		
		int ret;

		FILE* fp = NULL;
		char buff[1024];

		ret = recv(sock,&fi,sizeof(fi),0);
	/*	if(ret != 55)
		{
			fprintf(stderr,"error");
		}
	*/
		fp = fopen(fi.name,"wb");	
		while(1)
		{	
			ret = recv(sock,buff,sizeof(buff),0);

			fwrite(buff,1,ret,fp);

			if(ret == 0) break;	
		}
		fclose(fp);
	
	
	//第五步：断开连接（关闭套接字）
	
	close(sock);
	
	return 0;
}
