/*************************************************************
Name       : Dinesh Sandadi
Assignment : 2
DueDate    : 2/13/2017
Purpose    : server program that accepts the client requests and 
	     sends the daytime to client.
             
Function   : This program does the following steps
1) Creates Socket ,assign optional port number if given else sets
   to default port
2) Fills the socket address structure
3) Binds the socket to particulat port address, listens on that port
4) Accept the request from client and create another socket to handle that particular request 
5) writes data to socket from application buffer.Finally closes the socket. 
 ***************************************************************/

#include"wrap2srv.h"

extern bool servExitFlags[];

void setServExitFlags() {

    for (int i = 0; i < SNFLAGS + 1; i++)
        servExitFlags[i] = true;
}

int main(int argc, char *argv[]) {
    char buff[MAXLINE];				//Application buffer
    unsigned int port_number = SERV_PORT;	//assigning port number to default port number

//if argument count is 2 then assign second argument to portnumber.
    if (argc == 2)
        port_number = atoi(argv[1]);		//a to i converts string to integer.

//if argument count is greater than 2 then print error
    if ((argc > 2)) {
        fprintf(stderr, "Usage:<Port number>");
        exit(500);
    }

    setServExitFlags();

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);	//wrapper call to create a socket

    struct sockaddr_in servaddr;			//declaring the socketaddress structure
    servaddr.sin_family = AF_INET;			//filling in the structure family to be IPV4
    servaddr.sin_port = htons(port_number);		//converts portnumber to network byte order
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//This makes the server to accept client connections from multiple interfaces.

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));	//wrapper to bind socket to particular port address

    Listen(listenfd, LISTENEQ);				//wrapper to listen

    while (true) {
        int connfd = Accept(listenfd, NULL, NULL);	//wrapper to call accept,which accepts the client request
        time_t tkks = Time(0);				//Wrapper to system call time which returns the current time
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&tkks));//copies the time in to buffer.
        Write(connfd, buff, strlen(buff));		//writes into connfd socket from buffer
        Close(connfd);					//wrapper to close connfd socket
    }
    
}
