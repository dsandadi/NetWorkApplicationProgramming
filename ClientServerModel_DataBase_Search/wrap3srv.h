/*********************************
NAME       : DINESH SANDADI
ASSIGNMENT : 3
DUE DATE   : 3/10/2017 
PURPOSE    : Server Wrapper Header File
 *********************************/

#include"prog3srv.h"

#ifndef WRAP3_H
#define WRAP3_H

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

int Fclose(FILE *);

char *Fgets(char *, int, FILE *);

FILE *Fopen(const char *, const char *);

pid_t Fork(void);

int Fseek(FILE *, long, int);

pid_t Wait(int *);

typedef void Sigfunc(int);
Sigfunc* Signal(int, Sigfunc*);

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
#define FOPEN 9
#define FSEEK 10
#define WAIT 11
#define SIGNAL 12
#define FGETS 13
#define FCLOSE 14

#endif
