/*************************************************************
Name       : Dinesh Sandadi
Assignment : 5
DueDate    : 4/28/2017
Purpose    : server program that accepts the client requests and 
sends the name of the author of text book requested by client.

Function   : This program does the following steps
1) Creates Socket ,assign optional port number if given else sets
to default port
2) Fills the socket address structure
3) Binds the socket to particular port address, listens on that port
4) Accept the request from client and create another socket to handle that particular request 
5) writes data to socket from application buffer.Finally closes the socket. 
 ***************************************************************/

#include"prog5srv.h"
#include"wrap5srv.h"

extern bool servExitFlags[];

void setServExitFlags() {

    for (int i = 0; i < SNFLAGS + 1; i++)
        servExitFlags[i] = false;

    servExitFlags[SOCKET] = true;
    servExitFlags[LISTEN] = true;
    servExitFlags[BIND] = true;

}

int main(int argc, char *argv[]) {
    pid_t pid;
    //    char buff[MAXLINE];				//Application buffer
    unsigned int port_number = SERV_PORT;    //assigning port number to default port number

    //if argument count is 2 then assign second argument to portnumber.
    if (argc == 2)
        port_number = atoi(argv[1]);        //a to i converts string to integer.

    //if argument count is greater than 2 then print error
    if ((argc > 2)) {
        fprintf(stderr, "Usage:<Port number>");
        exit(500);
    }

    setServExitFlags();//setting servExitflags.

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);    //wrapper call to create a socket

    struct sockaddr_in servaddr;            //declaring the socketaddress structure
    servaddr.sin_family = AF_INET;            //filling in the structure family to be IPV4
    servaddr.sin_port = htons(port_number);        //converts portnumber to network byte order
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //This makes the server to accept client connections from multiple interfaces.

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));    //wrapper to bind socket to particular port address

    Listen(listenfd, LISTENEQ);                //wrapper to listen

    Signal(SIGCHLD, handler);

    while (true) {
        int connfd = Accept(listenfd, NULL, NULL);    //wrapper to call accept,which accepts the client request
        //creates a child process
        if ((pid = Fork()) == 0) {//job is assigned to child
            Close(listenfd);//closes the listening socket
            str_echo(connfd);//perform the intended task

            Close(connfd);//closes the socket
            exit(0);//exit successfully
        }

        Close(connfd);                    //wrapper to close connfd socket
    }

    Close(listenfd);
    exit(0);
}

/*****************************************
Function :handler
Purpose  : This function is called when ever
a signal is received by process 
from kernel.
 ******************************************/

void handler(int signo) {
    Signal(signo, handler);//activating the signal again
    Wait(0);
}
