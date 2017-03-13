/*******************************************
Name       : Dinesh Sandadi
Assignment : 3
Due Date   : 3/10/2017
Purpose    : HeaderFile for server program 
**********************************************/

#ifndef PROG3_H
#define PROG3_H

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"

#include<sys/types.h>   //includes standard information base library
#include<sys/wait.h>    //includes wait library
#include<string.h>      //for string manipulations
#include<strings.h>	//for bzero function
#include<stdlib.h>	//includes standard library
#include<sys/socket.h>	//includes socket() and connect () systemacalls
#include<unistd.h>	//includes system library for read() and write() systemcalls
#include<stdio.h>	//includes standard IO system library
#include<netinet/ip.h>	//includes socket structures
#include<errno.h>	
#include<signal.h>	//includes signal library

void str_author(int);	//doIt function prototype
void servSetExitFlags();//prototype
void handler(int);	//handler prototype

typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0

#define SA struct sockaddr	//define SA to be sockddr structure
#define SMAXLINE 1000        	//Buffer Length
#define SERV_PORT 9880        	//define default port number to 13
#define LISTENEQ 1000        	//size of listen queue length
#define DATAPATH "/home/cs631/common/books.d" //defining the path of the database file
#define SIZE 100

#endif
