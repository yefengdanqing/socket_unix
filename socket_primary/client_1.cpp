/*************************************************************************
	> File Name: client.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 04 Dec 2016 09:14:20 PM CST
 ************************************************************************/
//#include<ctypes>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string>
#include<string.h>
#include<fstream>
#include<stddef.h>

#define DEFAULT_PORT 8000

using namespace std;

int main(int argc,char* argv[])
{
	int sockfd,filefd;
	struct sockaddr_in clientaddr;
	if(argc!=3)
	{
		std::cout<<"used the ip"<<std::endl;
		//err_quit("usage : ip addr");
		return -1;
	}
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd==-1)
	{
		std::cout<<"init failure"<<std::endl;
		return -1;
	}
	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_port=htons (DEFAULT_PORT);
	if(inet_pton(AF_INET,argv[2],&clientaddr.sin_addr)<=0 )
	{
		std::cout<<"ip addr fault"<<std::endl;
		std::cout<<strerror(errno)<<" "<<errno<<std::endl;
		return -1;
	}
/*	if(-1==connect(sockfd,(sockaddr*)&clientaddr,sizeof(sockaddr)));
	{
		std::cout<<"don't connect'"<<std::endl;
		return -1;
	}*/
	if( connect(sockfd, (struct sockaddr*)&clientaddr, sizeof(clientaddr)) < 0)
	{
		    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
			exit(0);  
	}  
	//std::string sendbuf(argv[1]),recvbuf;
	char sendbuf[100]={0};
	char recvbuf[100]={0};
	strcpy(sendbuf,argv[1]);
	std::cout<<"send msg:" <<sendbuf<<std::endl;
	if(sendbuf==nullptr)
		return 0;
	//uint32_t sendlength=0;
	ssize_t sendlength=0;
	//sendlength=send(sockfd,sendbuf,strlen(sendbuf),0);
	sendlength=write(sockfd,sendbuf,strlen(sendbuf));
	if(sendlength<0||errno==EINTR)
	{
	std::cout<<"send failure"<<std::endl;
	 return 0;
	}
	char buf[300];
	ssize_t recvlength=0;
	recvlength=read(sockfd,buf,300);
	//recvlength=recv(sockfd,buf,30,0);
	//recvbuf=buf;
	buf[recvlength]='\0';
	strcpy(recvbuf,buf);
	if(recvlength==0)
	{
		std::cout<<"receive is 0"<<endl;
	}
	else
	{
		recvbuf[recvlength]='\0';
		std::cout<<recvlength<<std::endl;
		std::cout<<recvbuf<<std::endl;
	}
	exit(0);
	return 0;
};
