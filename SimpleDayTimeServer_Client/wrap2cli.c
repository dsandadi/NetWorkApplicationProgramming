/**********************************
NAME       : DINESH SANDADI
ASSIGNMENT : 2
DUE DATE   : 2/13/2017
PURPOSE    : CLIENT WRAPPER SOURCE CODE
Function   :
This Contains definitions of various wrapper functions.
Wrapper Function : It is the function which is used for checking if
any errors occured in calling system call and how to handle them 
i.e., whether to exit from program or continue. 
***********************************/

#include "wrap2cli.h"
#include "prog2cli.h"

bool exitFlag[NFLAGS + 1] = {false};

/*****************
close Wrapper function
fd: file descriptor
***************/
int Close(int fd) {
    errno = 0;//resetting errno global variable
    int r_value;
    
    if ((r_value = close(fd)) < 0) {
        //if system call returns negative value then displays error specified by user  along with the  system error and exit when ezit flag is set
        perror("can't close File");
	
        if (exitFlag[CLOSE])
            exit(CLOSE);
    }
    return r_value;
}

/*
Connect wrapper function definition
Arguments
sockfd   : socket file descriptor
sockaddr : general socket address structure
socklen_t: size of structure
*/
int Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
    errno = 0;//resetting errno to zero

    int r_value;

    if ((r_value = connect(sockfd, addr, addrlen)) < 0) {
        perror("can't connect");//if connection can't be made then print error

        if (exitFlag[CONNECT])
            exit(CONNECT);
    }
    return r_value;
}

/*Fputs Wrapper function definition
Arguments:
recv : Buffer
file : a file to write the contents of buffer
*/
int Fputs(const char *recv, FILE *file) {
    errno = 0;//resetting errno global variable

    int r_value;
    //if end of file is reached exit by printing the corresponding error

    if ((r_value = fputs(recv, file)) == EOF) {
        perror("Reached End of File");

        if (exitFlag[FPUTS])
            exit(FPUTS);
    }
    return r_value;
}

/************
Inet_pton function defintintion
family: internet famiily(IPV4,IPV6)
src   : address of server taken from command line arguments 
dst   : is a pointer that point to the destination address
**************/
int Inet_pton(int family, const char *src, void *dst) {
    errno = 0;

    int determiner = inet_pton(family, src, dst);
    //Two kinds of error one for determiner being negative which sets errno and the other one being ther determiner is zero,both are handled seperately

    if (determiner < 0) {
        perror("Error Address");
	
	if(exitFlag[INET_PTON])
        exit(2*INET_PTON);
    }

    if (determiner == 0) {
        fprintf(stderr, "inet_pton error: Invalid address \n");

        if (exitFlag[INET_PTON])
            exit(INET_PTON);
    }

    return determiner;
}

/**********************************************
Read wrapper function definition
fd   : file descriptor
buf  : buffer to store the data read from socket
count: number of bytes to read 
***********************************************/
ssize_t Read(int fd, void *buf, size_t count) {
    errno = 0;

    int n = read(fd, buf, count);
    //read () system call returns an integer value which determines if there is any error in reading a file

    if (n < 0)                //if return value is negative then errno is set
    {
        perror("Read Failed");//prints an error message along with the system error information

        if (exitFlag[READ])
            exit(READ);//exit
    }
    return n;
}

/*Socket() wrapper function defintion
domain   : internet protocol (IPV4 or IPV6)
type     : transport protocol( TCP or UDP)
protocol : this number is usually zero except when there are multiple protocols possible for particular domain and type
*/
int Socket(int domain, int type, int protocol) {
    errno = 0;//reset errno

    int sockfd = socket(domain, type, protocol);

    if (sockfd < 0) //if file descriptor returned is negative
    {
        perror("Socket Failed");//prints error info

        if (exitFlag[SOCKET])
            exit(SOCKET);//exit
    }
    return sockfd;
}
