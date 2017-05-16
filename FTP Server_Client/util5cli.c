/*************************************************************
Name       : Dinesh Sandadi
Assignment : 5
DueDate    : 4/28/2017
Purpose    : FTP User Interface.
Function   : This program does the following steps
 1) Takes the command from stdIn.
 2) Extracts the arguments from the command.
 3) Call the corresponding function of the command.
 ***************************************************************/

#include "prog5cli.h"
#include "wrap5cli.h"

//Initializing the commands array.
const char *cmds[] = {"", "?", "bye", "cd", "cdup", "close", "disconnect", "help", "lcd", "open", "pwd", "quit"};
const char *help_list[] = {"", "print local help information", "terminate ftp session and exit",
                           "change remote working directory", "change remote working directory to parent directory",
                           "terminate ftp session", "change local working directory", "connect to remote ftp",
                           "print working directory on remote machine", "terminate ftp session and exit"};


/*********************************
 *Arguments     : None
 *Return Value  : void
 *Description   : This function prints all the commands available in the ftp server.
 **********************************/

void prnt_cmd_list() {
    fprintf(stdout, "Commands maybe abbreviated.  Commands are:\n\n");
    //looping through all the commands.
    for (int i = 1; i < TOTALCOMMANDS; i++) {
        fprintf(stdout, "%-16s", cmds[i]);

        if (i % 5 == 0) printf("\n");// providing linefeed.

    }
    fflush(stdout);
}

/*********************************
 *Arguments     : char* (command)
 *Return Value  : cmd_id
 *Description   : This function returns the commandId of the input command.
 **********************************/


cmd_id find_id(char *cmd) {
    for (int i = 0; i < TOTALCOMMANDS; i++) {
        // if cmd is a null c string.
        if (strcmp(cmd, cmds[i]) == 0) {
            return i;
        }
    }
    return NEG_;
}

/*********************************
 *Arguments     : cmd
 *Return Value  : void
 *Description   : This function prints the description of the
 *                given command available in the ftp server.
 **********************************/
void prnt_cmd_help(char *cmd) {
    int commandId = find_id(cmd);// to store the commandId.

    //switch case to print the command corresponding the given input.
    switch (commandId) {
        case HELP_:
        case QM_:
            fprintf(stdout, "?               %s", help_list[1]);
            break;
        case BYE_:
            fprintf(stdout, "bye             %s", help_list[2]);
            break;
        case CD_:
            fprintf(stdout, "cd              %s", help_list[3]);
            break;
        case CDUP_:
            fprintf(stdout, "cdup            %s", help_list[4]);
            break;
        case CLOSE_:
            fprintf(stdout, "close           %s", help_list[5]);
            break;
        case DISCONNECT_:
            fprintf(stdout, "disconnect      %s", help_list[5]);
            break;
        case LCD_:
            fprintf(stdout, "lcd             %s", help_list[6]);
            break;
        case OPEN_:
            fprintf(stdout, "open            %s", help_list[7]);
            break;
        case PWD_:
            fprintf(stdout, "pwd             %s", help_list[8]);
            break;
        case QUIT_:
            fprintf(stdout, "quit            %s", help_list[9]);
    }
}

/*********************************
 *Arguments     : buf(that has the input line.), cmd(command),
 *                arg1(Argument 1),arg2 (Argument2) strings
 *Return Value  : cmd_id
 *Description   : This function extracts the commands
 *                and arguments from the given inputline.
 *
 **********************************/


cmd_id get_args(char *buf, char *cmd, char *arg1, char *arg2) {
    sscanf(buf, "%s%s%s", cmd, arg1, arg2);//extracting the arguments.
    return find_id(cmd);//returning the command Id.
}

/*********************************
 *Arguments     : directory name.
 *Return Value  : boolean value.
 *Description   : This function changes the directory
 *                to the specified directory.
 **********************************/


bool new_dir(char *dir) {
    char path[MAXLINE];//to store the path .
    strcpy(path, dir);//copying directory to path.
    char first[MAXLINE];//to store the first part of the path.
    char second[MAXLINE];//to store the second part of the path.
    sscanf(path, "%[^/]/%s", first, second);//extracting from path.

    //if first part is '~' then set the directory to home directory.
    if ((strcmp(first, "~") == 0) || strcmp(path, "") == 0)
        snprintf(path, sizeof(path), "%s/%s", getenv("HOME"), second);//printing to the path.

    Chdir(path);//changing directory to the path.

//checking errno
    if (errno == 0) {
        fprintf(stdout, "directory now %s\n", Getcwd(0, 0));
        return true;
    } else return false;
}
