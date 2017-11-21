#include<unistd.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>
#include"unp1.h"

#define MAXLINE 200
#define SIZE 1000
#define PORT 8181
#define MAXLIEN 200
int main()
{
	int sockfd,confd;
	int client_fd[SIZE];
	char buf[MAXLINE]={0};
	fd_set allset,rset;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	struct sockaddr_in serveraddr;
	//listen sock
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	serveraddr.sin_port=htons(PORT);
	bind(sockfd,(sockaddr*)&serveraddr,sizeof(sockaddr));

	listen(sockfd,10);
	int maxfd,maxi;
	maxi =-1;
	maxfd=sockfd+1;
	int client[SIZE];

	for(int i=0;i<SIZE;i++)
	{
		client[i]=-1;
	}
	FD_ZERO(&allset);
	FD_SET(sockfd,&allset);	
	socklen_t clientlen; //=sizeof(sockaddr_in);
	int i =0;
	int nearby = 0;
	while(1)
	{
		//allset = rset;
		rset = allset;
		//nearby = select(maxfd,&rset,NULL,NULL,0);
		nearby = select(maxfd,&allset,NULL,NULL,NULL);
		if(FD_ISSET(sockfd,&rset))
		{
			clientlen =sizeof(sockaddr_in);
			confd = accept(sockfd,(sockaddr*)&serveraddr,&clientlen);
			if(confd >0)
			{
				printf("client conection server.....\n");
			}
			//int i=0;
			for(i=0;i<SIZE;i++)
			{
				if(client[i]== -1)
				{
					client[i] = confd;
					break;
				}
			}
			//which set_fd
			FD_SET(confd,&allset);
			assert(i!=1024);
			if(confd>maxfd-1)
				maxfd=confd+1;
			if(i>maxi)
				maxi = i;
			//why
			if(nearby--<=0)
				continue;			
		}
		
			int temp_fd=0;
			for(int j=0;j<=maxi;j++)
			{
				temp_fd= client[j];
				if(temp_fd <=-1)
					continue;
				if(FD_ISSET(temp_fd,&allset))
				{
					int n=0;
					memset(buf,0,sizeof(buf));
					n=read(temp_fd,buf,MAXLIEN);
					if(n<=0)
					{
						printf("read failure\n");
						exit(0);
					}else
					{	
						printf("read msg:%s:%d\n",buf,n);
					}
					//char p[1] =static_cast<char>(j);
					char p =j+1;
					strcat(buf,&p);
					n=write(temp_fd,buf,n);
					if(n>0)
						printf("write num:%d\n",n);
					if(n== 0)
					{
						close(temp_fd);
						FD_CLR(temp_fd,&allset);
						client[j]= -1;
					}
					//write(temp_fd,buf,n)
				}
			}
		
	
	}
}
