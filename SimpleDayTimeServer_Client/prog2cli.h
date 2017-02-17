/*******************************************
Name       : Dinesh Sandadi
Assignment : 2
Due Date   : 2/13/2017
Purpose    : HeaderFile for client program 
**********************************************/

#ifndef PROG2_H
#define PROG2_H

#include "/home/cs631/common/config.h"

#include<sys/types.h>  //includes standard information base library
#include<strings.h>    //for bzero() function
#include<stdlib.h>     //includes standard library
#include<sys/socket.h> //includes socket() and connect () systemacalls
#include<unistd.h>     //includes system library for read() and write() systemcalls
#include<stdio.h>      //includes standard IO system library
#include<arpa/inet.h>  //includes system library for inet_pton() function
#include <netinet/ip.h>//includes socket structures

void setExitFlags();   //setExitFlags prototype

typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0

#define SA struct sockaddr //define SA to be sockddr structure
#define MAXLINE 40         //Buffer Length 
#define SERV_PORT 9880     //default port

#endif
