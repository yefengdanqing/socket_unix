//server.cpp
/*************************************************************************
	> File Name: server.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 05 Dec 2016 08:31:11 PM CST
 ************************************************************************/

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstddef>
#include<string>
#include<cstring>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>
#include<fstream>

#define DEFAULT_PORT 8000


int main(int argc,char* argv[])
{
	int sockfd,condfd;
	pid_t  childpid;
	socklen_t clientlen;
	char recvbuf[30]={0};
	struct sockaddr_in seraddr,clientaddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(DEFAULT_PORT); 
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if((sockfd=socket(AF_INET,SOCK_STREAM,0)) <0)
	{
		std::cout<<"init error"<<std::endl;
		return -1;
	}
	if(-1==bind(sockfd,(sockaddr*)&seraddr,sizeof(sockaddr)) )
	{
		std::cout<<"bind failure"<<std::endl;
		return -1;
	}
	if(-1==listen(sockfd,5) )
	{
		std::cout<<"listen fail"<<std::endl;
		return -1;
	}

	while(1)
	{
		clientlen=sizeof(clientaddr);
		condfd=accept(sockfd,(sockaddr*)&clientaddr,&clientlen);
		 if(-1==condfd)
		 {
			 std::cout<<"no accept"<<std::endl;
			 return -1;
		 }
		ssize_t n=read(condfd,recvbuf,29);
		//ssize_t n=recv(condfd,recvbuf,29,0);
		recvbuf[n]='\0';
		std::cout<<"start read......"<<std::endl;
		std::cout<<recvbuf<<std::endl;
		strcpy(recvbuf+n,"already recv");
		//send(condfd,recvbuf,sizeof(recvbuf),0);
		write(condfd,recvbuf,sizeof(recvbuf));
		close(condfd);
	}
}
