#include"prog5srv.h"
#include"wrap5srv.h"

const char *cmds[] = {"", "?", "bye", "cd", "cdup", "close", "disconnect", "help", "lcd", "open", "pwd", "quit"};

/**************************************************
 *
 * str_echo
 * Arguments    :connfd file descriptor.
 * Return value : void
 * Description  : This function Reads from the socket and
 * replies to the client the output of the given command.
 *
 **********************************************/

void str_echo(int connfd) {

    //variable declaration
    char cmd[SIZE];//cmd to store the command.
    char arg1[SIZE];//to store the argument1.
    char arg2[SIZE];//to store the argument2.
    cmd_id commandID;//to store the commandId
    char input[MAXLINE];//to store the input.
    char sendLine[MAXLINE];//to store the line that has to be sent.
    char *output;//to store the output.
    int size; // to store the size.
    //while loop to read from socket line by line

    while ((size = Readline(connfd, input, SMAXLINE)) > 0) {

        input[strlen(input) - 1] = 0;//setting input last character to null value.
        commandID = get_args(input, cmd, arg1, arg2);//getting the commandId.

        //switching based on the commadID
        switch (commandID) {
            case PWD_:
                output = Getcwd(0, 0);//getting the current working directory.
                snprintf(sendLine, sizeof(sendLine), "%d:\"%s\" is current direcotry.\n", errno, output);
                break;
            case CD_:
                new_dir(arg1);
                if (errno == 0)//errno checking.
                    snprintf(sendLine, sizeof(sendLine), "%d:CWD command successful.\n", errno);
                else
                    snprintf(sendLine, sizeof(sendLine), "%d:\n", errno);

                break;
            case CDUP_:
                Chdir("..");//changing directory up.
                if (errno == 0)//checking errno value.
                    snprintf(sendLine, sizeof(sendLine), "%d:CWD command successful.\n", errno);
                else
                    snprintf(sendLine, sizeof(sendLine), "%d:\n", errno);
                break;
	  default:
                goto endWhile;
        }
        Writen(connfd, sendLine, strlen(sendLine));//writing in to the socket.
        endWhile:;
    }
    return;
}

/*
Function: find_id.
Return type: return the command Id.
Arguments  : cmd string that contains the command.
*/
cmd_id find_id(char *cmd) {

    //looping through all the commands.
    for (int i = 0; i < TOTALCOMMANDS; i++) {

        if (strcmp(cmd, cmds[i]) == 0) {
            return i;
        }
    }
    return NEG_;
}

/*
Function   : get_args
Return type: returns the command id of extracted command.
Arguments  : buffer containing the command, extracted command, extracted arguments.
*/
cmd_id get_args(char *buf, char *cmd, char *arg1, char *arg2) {
    sscanf(buf, "%s%s%s", cmd, arg1, arg2);
    return find_id(cmd);
}

/*Function  :new_dir
Return type : returns boolean value whether directory is changed or not
Arguments   : directory name to change.
*/
bool new_dir(char *dir) {
    //comparing the dir to null string.
    if (strcmp(dir, "") == 0) {
        return true;
    }
    char path[MAXLINE];//to store the path .
    strcpy(path, dir);//copying directory to path.
    char first[MAXLINE];//to store the first part of the path.
    char second[MAXLINE];//to store the second part of the path.
    sscanf(path, "%[^/]/%s", first, second);//extracting from path.

    if (strcmp(first, TILDA) == 0)
        snprintf(path, sizeof(path), "%s/%s", getenv("HOME"), second);

    Chdir(path);//calling the chdir systemcall.

// checking errno.
    if (errno == 0) {
        return true;
    } else return false;
}



