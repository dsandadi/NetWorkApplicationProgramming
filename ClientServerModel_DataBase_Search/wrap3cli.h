/*********************************
NAME       : DINESH SANDADI
ASSIGNMENT : 3
DUE DATE   : 3/10/2017 
PURPOSE    : Wrapper Header File
 *********************************/

#include"prog3cli.h"

#ifndef WRAP3_H
#define WRAP3_H

#include<errno.h>

/***************************************Wrapper Function prototypes*********************************************************
Socket   : This wrapper function calls the socket system call and exits if there is any error in creating socket
Close    : This wrapper function calls the close system call and exits if the corresponding file can't be closed
Connect  : 
This wrapper function calls the connect system call and exits if the connection can't be made to the specified server address
Fputs    : This wrapper function calls fputs system call and exits on reaching the end of file setting the errno.
Inet_pton: 
This wrapper function calls the inet_pton system call to convert the ip address from presentation to network byte order and exits 
on failure to do so. There are two kinds of errors : one that sets the errno specifying error produced by systemcall ,another 
which doesn't set errno, each are handled seperatley
Readline  : 
This wrapper function calls readline() library call to read a line from socket into buffer and exits on any error in reading from socket
Writen    :
This wrapper function calls writen() library call which writes n bytes into socket
*****************************************************************************************************************************/

int Socket(int, int, int);

int Close(int);

int Connect(int, struct sockaddr *, socklen_t);

int Fputs(const char *, FILE *);

int Inet_pton(int, const char *, void *);

ssize_t Readline(int, void *, size_t);

ssize_t Writen(int, const void *, size_t);

char *Fgets(char *, int, FILE *);

//exitflags constants
#define NFLAGS 8 //number of flags are equal to number of wrapper functions
#define NOERROR 0
#define SOCKET 1
#define CLOSE 2
#define CONNECT 3
#define FPUTS 4
#define INET_PTON 5
#define READLINE 6
#define WRITEN 7
#define FGETS 8

#endif
