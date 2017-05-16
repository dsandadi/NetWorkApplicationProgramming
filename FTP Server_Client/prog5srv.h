/*******************************************
Name       : Dinesh Sandadi
Assignment : 5
Due Date   : 4/28/2017
Purpose    : HeaderFile for server program 
**********************************************/

#ifndef PROG5_H
#define PROG5_H


//enum datatype
typedef enum {
    NEG_ = -1, ZERO_, QM_, BYE_, CD_, CDUP_, CLOSE_, DISCONNECT_, HELP_, LCD_, OPEN_, PWD_, QUIT_
} cmd_id;


typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0

void str_echo(int);     //doIt function prototype
void servSetExitFlags();//prototype//implemented
void handler(int);      //handler prototype//implemented
cmd_id find_id(char *);//implemented
cmd_id get_args(char *, char *, char *, char *);//get_args
bool new_dir(char *);

#define SA struct sockaddr        //define SA to be sockddr structure
#define SMAXLINE 1000            //Buffer Length
#define SERV_PORT 9880            //define default port number to 13
#define LISTENEQ 1000            //size of listen queue length
#define SIZE 100                // defining size.
#define TOTALCOMMANDS 11        //definig total commands.
#define TILDA "~"               // defining tilda.

#endif
