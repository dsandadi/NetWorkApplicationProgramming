/********************
NAME:DINESH SANDADI
ASSIGNMENT 1
FUNCTION:WRAPPER SOURCE
********************/
#include"wrap1cli.h"
void Close(int fd){
errno=0;
if(close(fd)<0) {perror("can't close File");
exit(3);
}

}
void Connect(int sockfd,struct sockaddr * addr,socklen_t addrlen)
{
errno=0;
if(connect(sockfd,addr,addrlen)<0) {perror("can't connect");
exit(5);
}
}
void Fputs(const char * recv ,FILE * file)
{
errno=0;
if(fputs(recv,file)==EOF) {
perror("Reached End of File");
exit(7);
}
}
void Inet_pton(int family,const char * src, void * dst)
{
errno=0;
int determiner=inet_pton(family,src,dst);
if(determiner<0) {
perror("Error Address");
exit(6);}
if(determiner==0)
{
fprintf(stderr,"inet_pton error: Invalid address \n");
exit(4);
}
}
ssize_t Read(int fd,void * buf,size_t count)
{
errno=0;
int n=read(fd,buf,count);
if(n<0)
{
perror("Read Failed");
exit(9);
}
return n;
}
int Socket(int domain,int type,int protocol)
{
errno =0;
int sockfd=socket(domain,type,protocol);
if(sockfd<0) 
{perror("Socket Failed");
exit(11);
}
return sockfd;
}
