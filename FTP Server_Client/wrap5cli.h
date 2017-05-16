/*********************************
NAME       : DINESH SANDADI
ASSIGNMENT : 5
DUE DATE   : 4/28/2017 
PURPOSE    : Wrapper Header File
 *********************************/

#ifndef WRAP5_H
#define WRAP5_H

#include<errno.h>
#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"

#include<sys/types.h>   //includes standard information base library
#include<strings.h>     //for bzero() function
#include<stdlib.h>      //includes standard library
#include<sys/socket.h>  //includes socket() and connect () systemacalls
#include<unistd.h>      //includes system library for read() and write() systemcalls
#include<stdio.h>       //includes standard IO system library
#include<arpa/inet.h>   //includes system library for inet_pton() function
#include <netinet/ip.h> //includes socket structures

typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0


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
Chdir     :

Getcwd    : This function returns the current working directory.errno is checked here.

Chdir     : changes the directory to the given directory. errno is checked here.
*****************************************************************************************************************************/

int Socket(int, int, int);

int Close(int);

int Connect(int, struct sockaddr *, socklen_t);

int Fputs(const char *, FILE *);

int Inet_pton(int, const char *, void *);

ssize_t Readline(int, void *, size_t);

ssize_t Writen(int, const void *, size_t);

char *Fgets(char *, int, FILE *);

int Chdir(const char *);

char *Getcwd(char *, size_t);


//exitflags constants
#define NFLAGS 10 //number of flags are equal to number of wrapper functions
#define NOERROR 0
#define SOCKET 1
#define CLOSE 2
#define CONNECT 3
#define FPUTS 4
#define INET_PTON 5
#define READLINE 6
#define WRITEN 7
#define FGETS 8
#define GETCWD 9
#define CHDIR 10

#endif
