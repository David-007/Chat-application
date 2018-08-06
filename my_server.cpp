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
	int sockfd,newfd,prt;
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(argc < 2)
		error("No port available");
	prt=atoi(argv[1]);
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(prt);
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,8);
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server)) < 0)
		error("Bind");
	if(listen(sockfd,5) < 0)
		error("Listen");
	unsigned int clilen;
	clilen=sizeof(struct sockaddr_in);
	if((newfd=accept(sockfd,(struct sockaddr*)&client,&clilen)) < 0)
		error("Accept");
	int pid=fork();
	if(pid > 0){
		char msg[100];
		while(1){
			memset(msg,'\0',100);
			recv(newfd,msg,100,0);
			cout<<msg<<endl;
		}	
	}
	else{
		char msg[100];
		while(1){
			memset(msg,'\0',100);
			cin.getline(msg,100);
			send(newfd,msg,100,0);	
		}
	}
	return 0;
}
