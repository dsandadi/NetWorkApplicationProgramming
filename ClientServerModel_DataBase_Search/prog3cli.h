/*******************************************
Name       : Dinesh Sandadi
Assignment : 3
Due Date   : 3/10/2017
Purpose    : HeaderFile for client program 
**********************************************/

#ifndef PROG3_H
#define PROG3_H

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

void setExitFlags();   //setExitFlags prototype
void str_cli(int);

typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0

#define SA struct sockaddr //define SA to be sockddr structure
#define SERV_PORT 9880     //default port
#define LENGTH 200         //length constant
#define CMAXLINE 1000      //client maxline constant

#endif
