/*********************************
NAME       : DINESH SANDADI
ASSIGNMENT : 2
DUE DATE   : 2/13/2017 
PURPOSE    : Server Wrapper Header File
 *********************************/

#include"prog2srv.h"

#ifndef WRAP3_H
#define WRAP3_H

/***************************************Wrapper Function prototypes*********************************************************
Socket   : This wrapper function calls the socket system call and exits if there is any error in creating 	    socket
Close    : This wrapper function calls the close system call and exits if the corresponding file can't be 	    closed
Bind     : Binds the socket to particular port address
Listen   : This wrapper function makes the socket to wait for connections
Accept   : This wrapper function accepts the connection and create another socket to handle the client 
	   request
write    : This wrapper function writes the application data to socket.
Time     : This wrapper function returns the present time of the day.
*****************************************************************************************************************************/

int Socket(int, int, int);

int Close(int);

int Bind(int, const struct sockaddr *, socklen_t);

int Listen(int, int);

int Accept(int, struct sockaddr *, socklen_t *);

ssize_t Write(int, const void *, size_t);

time_t Time(time_t *);

//exit flags constants definition
#define SNFLAGS  7 //server number of flags are equal to number of wrapper functions
#define NOERROR 0
#define SOCKET 1
#define CLOSE 2
#define BIND 3
#define LISTEN 4
#define ACCEPT 5
#define WRITE 6
#define TIME 7

#endif
