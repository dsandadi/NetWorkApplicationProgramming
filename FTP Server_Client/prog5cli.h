/*******************************************
Name       : Dinesh Sandadi
Assignment : 5
Due Date   : 4/28/2017
Purpose    : HeaderFile for client program 
**********************************************/

#ifndef PROG5_H
#define PROG5_H

//enum datatype
typedef enum {
    NEG_ = -1, ZERO_, QM_, BYE_, CD_, CDUP_, CLOSE_, DISCONNECT_, HELP_, LCD_, OPEN_, PWD_, QUIT_
} cmd_id;

//defining boolean datatype
typedef int bool;
//Since bool datatype is not available in C .I used integer datatype to represent boolean value
#define true 1
#define false 0

//client utilities functions 
void setExitFlags();   //setExitFlags prototype

bool str_cli(int, char *);     //str_cli prototype.

void prnt_cmd_list();  //prnt_cmd_list prototype.

void prnt_cmd_help(char *); //prnt_cmd_help prototype.

cmd_id find_id(char *);     //find_id prototype.

cmd_id get_args(char *, char *, char *, char *);  //get_args() prototype.

bool client(char *, char *, bool); //client prototype.

cmd_id find_id(char *);   //find_id prototype.

bool new_dir(char *dir);   //new_dir prototype.

#define SA struct sockaddr //define SA to be sockddr structure
#define SERV_PORT 9880     //default port
#define LENGTH 200         //length constant
#define CMAXLINE 1000      //client maxline constant
#define TOTALCOMMANDS 12   //Total commands available in FTP
#define PRMT "ftp> "       //defininig prompt
#define INV_CMD "?Invalid command\n"  //defining invalid command.

#endif
