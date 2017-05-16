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

//inlcuding libraries.
#include"prog5cli.h"
#include"wrap5cli.h"

int main() {
    char buf[MAXLINE];//buffer to store the inputline.
    char cmd[MAXLINE];//buffer to store the command.
    char arg1[MAXLINE];//buffer to store the argument1.
    char arg2[MAXLINE];//buffer to store the argument2.

    int cmd_id;//commandId
    bool prompt = true; // prompt local variable.

    //infinite loop.
    while (true) {
        //clearing the buffers
        bzero(cmd, sizeof(cmd));
        bzero(arg1, sizeof(arg1));
        bzero(arg2, sizeof(arg2));
        bzero(buf, sizeof(buf));

        cmd_id = 0;//set commandId to zero.

        fprintf(stdout, PRMT);
        Fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = 0;

        cmd_id = get_args(buf, cmd, arg1, arg2);//extracting the commandId.

        //switch case based on the commandId.
        switch (cmd_id) {
            //Invalid command.
            case NEG_:
                fprintf(stdout, INV_CMD);
                break;
                //No command.
            case ZERO_:
                break;
                //Question mark command or help command.
            case QM_:
            case HELP_:
                if (strcmp(arg1, "") != 0) {
                    prnt_cmd_help(arg1);
                } else {
                    prnt_cmd_list();
                }
                printf("\n");
                break;
                //quit or bye command.
            case QUIT_:
            case BYE_:
                exit(0);

                //LCD_ command.
            case LCD_:
                if (!new_dir(arg1))
                    fprintf(stderr, "local : %s:%s\n",arg1, strerror(errno));
                break;

                //open command.
            case OPEN_:
                if (strcmp(arg1, "") != 0) {
                    if (client(arg1, arg2, prompt))// if client returns true exit.
                        exit(0);
                } else {
                    fprintf(stdout, "(to) ");
                    char tempLine[MAXLINE];
                    Fgets(tempLine, sizeof(tempLine), stdin);
                    tempLine[strlen(tempLine) - 1] = 0;
                    sscanf(tempLine, "%s%s", arg1, arg2);
                    if (strcmp(arg1, "") != 0) {
                        if (client(arg1, arg2, prompt)) //if client returns true exit.
                            exit(0);
                    } else {
                        fprintf(stdout, "usage: open host-name [port]");
                        break;
                    }
                }
                break;

                //not any command declared above.
            default:
                fprintf(stdout, "Not connected.");
                printf("\n");
                break;
        }
    }

}
