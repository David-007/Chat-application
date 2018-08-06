#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;
void error(const char *msg){
	perror(msg);
	exit(-1);
}
int main(int argc,char *argv[]) {
	int sockfd,newfd,prt,clilen;
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(argc < 2)
		error("No port available");
	prt=atoi(argv[1]);
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(prt);
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,8);

	if((connect(sockfd,(struct sockaddr*)&server,sizeof(server))) < 0)
		error("Connect");
	int pid=fork();
	if(pid > 0){
		char msg[100];
		while(1){
			memset(msg,'\0',100);
			cin.getline(msg,100);
			send(sockfd,msg,100,0);	
		}
	}
	else{
		char msg[100];
		while(1){
			memset(msg,'\0',100);
			recv(sockfd,msg,100,0);
			cout<<msg<<endl;
		}
	}
	return 0;
}
