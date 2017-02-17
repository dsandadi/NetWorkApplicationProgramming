/**********************
NAME:DINESH SANDADI
ASSIGNMENT 1 
FUNCTION: Wrapper Header File
**********************/
#ifndef WRAP1_H
#define WRAP1_H
#include"prog1cli.h"
#include<errno.h>
int Socket(int,int,int);
void Close(int );
void Connect(int,struct sockaddr*, socklen_t);
void Fputs(const char* ,FILE*);
void Inet_pton(int ,const char * , void*);
ssize_t Read(int,void* ,size_t);
#endif
