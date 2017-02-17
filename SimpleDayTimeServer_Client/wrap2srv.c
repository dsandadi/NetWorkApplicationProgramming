/*******************************************************************
NAME       : DINESH SANDADI
ASSIGNMENT : 2
DUE DATE   : 2/13/2017
PURPOSE    : SERVER WRAPPER SOURCE CODE
Function   : This Contains definitions of 
	     various wrapper functions.
Wrapper Function : It is the function which is used for checking if
any errors occured in calling system call and how to handle them
i.e., whether to exit from program ot continue.
********************************************************************/

#include "wrap2srv.h"

bool servExitFlags[SNFLAGS + 1] = {false};

/*Socket() wrapper function defintion
domain   : internet protocol (IPV4 or IPV6)
type     : transport protocol( TCP or UDP)
protocol : this number is usually zero except when there are multiple protocols possible for particular domain and type
*/

int Socket(int family, int type, int protocol) {

    errno = 0;				//resetting errno to zero

    int determiner = socket(family, type, protocol);

    if (determiner < 0)			//if determiner is negative
    {
        perror("Socket is not created");

        if (servExitFlags[SOCKET])	//if flag is set then exit
            exit(SOCKET);

    }

    return determiner;

}

/*
Function  : Bind(int,const struct sockaddr* , socklen_t)
Arguments : 
sockfd:socket file descriptor
sockaddr* : pointer to the socket address structure
addrlen   : length of socket address structure
*/
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {

    errno = 0;						//setting errno to zero

    int r_value;					//return value

    if ((r_value = bind(sockfd, addr, addrlen)) < 0)	//if return value is negative then system error
    {
        perror("can't bind socket to local address");

        if (servExitFlags[BIND])
            exit(BIND);

    }
    return r_value;

}

/*
Function :Listen (int ,int)
Purpose  :To make socket listen on particular port
Arguments :
sockfd  : socket file descriptor
backlog : length of queue  
*/
int Listen(int sockfd, int backlog) {

    errno = 0;//setting errno to zero

    int r_value;

    if ((r_value = listen(sockfd, backlog)) < 0)//if return value is negative
    {
        perror("Error in listening");

        if (servExitFlags[LISTEN])		//if flag is set
            exit(LISTEN);

    }
    return r_value;

}

/*
Function : Accept(int, struct sockaddr * ,socklent_t * )
purpose  : To accept the client request and create a new socket
Arguments :
sockfd  : socket file descriptor
addr    : pointer to sockaddr structure
addrlen : pointer to the socklent_t  
*/
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {

    errno = 0;					//sets errno to zero

    int fd = accept(sockfd, addr, addrlen);	//returns newly created socket file descriptor

    if (fd < 0)					//if file descriptor is negative
    {
        perror("can't accept the request");

        if (servExitFlags[ACCEPT])			//if flag is set then exit
            exit(ACCEPT);

    }

	return fd;
}

/*
Function : write(int ,const void *,size_t )
purpose  : to write the data into socket
Arguments: 
fd   : filedescriptor
buf  : pointer to the application buffer
count: size of the data to copy 
*/
ssize_t Write(int fd, const void *buf, size_t count) {

    errno = 0;					//set errno to zero

    ssize_t r_value;

    if ((r_value = write(fd, buf, count)) < 0)	//if return value is negative
    {
        perror("can't write in to socket");

        if (servExitFlags[WRITE])//if exit flag is set
            exit(WRITE);

    }

    return r_value;
}

/*
Function : close(int ) 
purpose  : to close the file with file descriptor fd
*/
int Close(int fd) {

    errno = 0;//setting errno to zero

    int r_value;

    if ((r_value = close(fd)) < 0) //if return value is negative
    {
        perror("can't close file");

        if (servExitFlags[CLOSE])//if exit flag is set
            exit(CLOSE);
    }

    return r_value;
}

/*
Function : time (time_t * )
purpose  : This function returns the current time of the day.
*/
time_t Time(time_t *t) {

    errno = 0;

    time_t tkks = time(t);

    if (tkks < 0)//if tkks is negative then system error
    {
        perror("Clock Error");

        if (servExitFlags[TIME])//if flag is set
            exit(TIME);

    }

    return tkks;

}
