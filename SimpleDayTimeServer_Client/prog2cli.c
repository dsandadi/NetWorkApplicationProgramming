/*************************************************************
Name       : Dinesh Sandadi
Assignment : 2
DueDate    : 2/13/2017
Purpose    : Client program that requests the server for daytime 
	     by optional port number.
Function   : This program does the following steps
1) Creates Socket ,assign optional port number if given else sets 
   to default port  
2) Fills the socket address structure
3) Connects to the server and Retrieves data from server
4) Reads the data from socket to buffer and finally closes the socket.
 ***************************************************************/

#include"wrap2cli.h"//includes userdefined header for wrapper

extern bool exitFlag[];

/*
Function : setExitFlags() 
Purpose  : sets exitflags to determine whether to exit from program or not.
*/
void setExitFlags() {

    for (int i = 0; i < NFLAGS + 1; i++) {

        exitFlag[i] = true;

    }

}

int main(int argc, char **argv) {
    int sockfd, size;           //declaring file descriptor
    char recv[MAXLINE + 1];     //declaring an application buffer
    struct sockaddr_in address; //declaring address as sockaddress structure for IPV4
    unsigned int port_number;            //declaring port_number variable

    setExitFlags();             //calling setExitFlags () function

    if (argc != 3 && argc != 2) //if arguments are too few then exit from program
    {
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);//print message on stderror
        exit(55);                                           //exit
    }

    port_number = (argc == 2) ? SERV_PORT : atoi(argv[2]);
    //sets the port number to default port if no arguments are provides else sets it to provided argument

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);      //calling Socket wrapper function
    bzero(&address, sizeof(address));              //clearing the address structure
    address.sin_family = AF_INET;                  //setting the family to be of IPV4
    address.sin_port = htons(port_number);         //setting port number to optional value
    Inet_pton(AF_INET, argv[1], &address.sin_addr);//converts destination address to network byte order

    Connect(sockfd, (SA *) &address, sizeof(address));//calls Connect wrapper function

    while ((size = Read(sockfd, recv, MAXLINE)) > 0)//Reading the data from socket
    {
        recv[size] = 0;                             //setting either return or carry bits to zero
        Fputs(recv, stdout);                        //putting on received doata on to stdout ,monitor.
    }

    Close(sockfd);                                  //close socket file

    if (exitFlag[NOERROR])
        exit(NOERROR);                                    //exit successfully
}
