#include"prog1cli.h"
#include"wrap1cli.h"
int main(int argc,char ** argv)
{
int sockfd,size;
char recv[MAXLINE+1];
struct sockaddr_in address;
//struct sockaddr SA;
if(argc!=2) 
{
fprintf(stderr,"usage:%s <IPaddress>\n",argv[0]);
exit(55);
}
sockfd=Socket(AF_INET,SOCK_STREAM,0);
bzero(&address, sizeof(address));
address.sin_family=AF_INET;
address.sin_port=htons(13);
Inet_pton(AF_INET,argv[1],&address.sin_addr);
int k=connect(sockfd ,(SA *) &address, sizeof(address));
if(k<0) exit(1);
while((size=Read(sockfd,recv,MAXLINE))>0)
{recv[size]=0;
Fputs(recv,stdout);
}
Close(sockfd);
exit(0);
}
