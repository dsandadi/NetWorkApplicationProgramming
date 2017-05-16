/*********************************
NAME       : DINESH SANDADI
ASSIGNMENT : 5
DUE DATE   : 4/28/2017 
PURPOSE    : Server Wrapper Header File
 *********************************/

#ifndef WRAP5_H
#define WRAP5_H

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"

#include<sys/types.h>   //includes standard information base library
#include<sys/wait.h>    //includes wait library
#include<string.h>      //for string manipulations
#include<strings.h>     //for bzero function
#include<stdlib.h>      //includes standard library
#include<sys/socket.h>  //includes socket() and connect () systemacalls
#include<unistd.h>      //includes system library for read() and write() systemcalls
#include<stdio.h>       //includes standard IO system library
#include<netinet/ip.h>  //includes socket structures
#include<errno.h>
#include<signal.h>      //includes signal library


/***************************************Wrapper Function prototypes*********************************************************
Socket   : This wrapper function calls the socket system call and exits if there is any error in creating 	    socket
Close    : This wrapper function calls the close system call and exits if the corresponding file can't be 	    closed
Bind     : Binds the socket to particular port address
Listen   : This wrapper function makes the socket to wait for connections
Accept   : This wrapper function accepts the connection and create another socket to handle the client 
	   request
Readline() : This wrapper function reads from a file line by line i.e., until a new line character is reached
writen    : This wrapper function writes  n bytes from the application buffer to socket.
Fclose    : This wrapper closes the file
Fgets()   : This wrapper is to get a line from file and store that into string
Fopen()   : opens a file
Fork()    : This wrapper function creates a child process
Fseek()   : This wrapper is used to set the position of file pointer
Wait()    : This wrapper makes the parent process wait until the child process exits .
Signal()  : This wrapper function calls the signal system call which activates the signal.
 *****************************************************************************************************************************/

int Socket(int, int, int);

int Close(int);

int Bind(int, const struct sockaddr *, socklen_t);

int Listen(int, int);

int Accept(int, struct sockaddr *, socklen_t *);

ssize_t Writen(int, const void *, size_t);

ssize_t Readline(int, void *, size_t);

pid_t Fork(void);

pid_t Wait(int *);

typedef void Sigfunc(int);

Sigfunc *Signal(int, Sigfunc *);

int Chdir(const char *);

char *Getcwd(char *, size_t);

//exit flags constants definition
#define SNFLAGS  14 //server number of flags are equal to number of wrapper functions
#define NOERROR 0
#define SOCKET 1
#define CLOSE 2
#define BIND 3
#define LISTEN 4
#define ACCEPT 5
#define WRITEN 6
#define READLINE 7
#define FORK 8
#define WAIT 11
#define SIGNAL 12
#define FGETS 13
#define FCLOSE 14
#define CHDIR 10
#define GETCWD 9

typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0

#endif
