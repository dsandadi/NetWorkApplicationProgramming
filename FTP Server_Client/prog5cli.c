/*************************************************************
Name       : Dinesh Sandadi
Assignment : 5
DueDate    : 4/28/2017
Purpose    : Client program that requests the server for author name
by optional port number.
Function   : This program does the following steps
1) Creates Socket ,assign optional port number if given else sets 
to default port  
2) Fills the socket address structure
3) Connects to the server and writes data into socket, Retrieves data from server
4) Reads the data from socket to buffer and finally closes the socket.
 ***************************************************************/

#include"prog5cli.h"
#include"wrap5cli.h"

extern bool exitFlag[];

/*
Function : setExitFlags() 
Purpose  : sets exitflags to determine whether to exit from program or not.
 */
void setExitFlags() {

    for (int i = 0; i < NFLAGS + 1; i++) {

        exitFlag[i] = false;// all exit flags set to false.

    }

}

/*
 * Function   : client()
 * Purpose    : connects to the server on given arguments.
 * returnType : returns true up on exiting successfully.
 */

bool client(char *arg1, char *arg2, bool prompt) {
    int sockfd;           //declaring file descriptor
    struct sockaddr_in address; //declaring address as sockaddress structure for IPV4
    unsigned int port_number;            //declaring port_number variable
    int determiner; //declaring the determiner variable.

    setExitFlags();             //calling setExitFlags () function

    if (!arg1) //if arguments are too few then exit from program
    {
        fprintf(stderr, "usage: %s <IPaddress>\n", arg1);//print message on stderror
    }

    port_number = (strcmp(arg2, "") == 0) ? SERV_PORT : atoi(arg2);
    //sets the port number to default port if no arguments are provides else sets it to provided argument

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);      //calling Socket wrapper function

    if (errno != 0) return false;

    bzero(&address, sizeof(address));              //clearing the address structure


    address.sin_family = AF_INET;                  //setting the family to be of IPV4

    address.sin_port = htons(port_number);         //setting port number to optional value


    determiner = Inet_pton(AF_INET, arg1, &address.sin_addr);//converts destination address to network byte order

    if ((errno != 0) || (errno == 0 && determiner == 0)) return false;

    Connect(sockfd, (SA *) &address, sizeof(address));//calls Connect wrapper function

    if (errno != 0) return false;
    printf("Connected to %s.\n", arg1);

    //calls the function to request data from server
    bool breakPoint = str_cli(sockfd, arg1);

    Close(sockfd);//close socket file

    if (prompt)
        printf("Goodbye.\n");

    return breakPoint;
}

/****************************************************
 * Function     : str_cli(int)
 * Return value : void
 * purpose      : Takes the book name from the
 *                stdin and sends it to the server
 *                , and also retrieves the auidthor
 *                name from server
 ***************************************************/
bool str_cli(int sockfd, char *saddr) {
    char recv[CMAXLINE + 1];     //declaring an application buffer to receive the data from socket
    char input[LENGTH];    // to write the data from application to socket
    char display[LENGTH];//display string.
    cmd_id comdId;  // commandId of the command.
    char cmd[CMAXLINE]; // buffer to store the command.
    char errArg[LENGTH]; //buffer to store the error sent by server.
    char arg1[CMAXLINE], arg2[CMAXLINE]; // buffers to store the arguments.
    fprintf(stdout, PRMT);
    fflush(stdout);
    //while loop for accepting the input from user
    while ((Fgets(input, sizeof(input), stdin)) != NULL) {
        input[strlen(input) - 1] = 0;//setting the last character to null.
       
	//clearing buffers.
        bzero(cmd,sizeof(cmd));
	bzero(arg1,sizeof(arg1));
	bzero(arg2,sizeof(arg2));

	comdId = get_args(input, cmd, arg1, arg2); //getting the commandId.
	input[strlen(input)] = '\n';//setting last character to new line character.
        //switch to the corresponding command.
        switch (comdId) {

            case CLOSE_:
            case DISCONNECT_:
                goto endWhile; //comes out of  the loop.

            case QUIT_:
            case BYE_:
                return true;

                //case for cdup and pwd.
            case CDUP_:
            case PWD_:
                Writen(sockfd, input, strlen(input));//writes n bytes into socket
                break;

//case for cd command.
            case CD_:
                if (strcmp(arg1, "") == 0) {
                    printf("(remote-directory) ");
                    char input2[LENGTH];//buffer to store the second argument(to address).
                    Fgets(input2, sizeof(input2), stdin);//getting the input.
                    snprintf(input, sizeof(input), "cd %s", input2);//writes into string.
                    Writen(sockfd, input, strlen(input));//writes into socket.
                } else
                    Writen(sockfd, input, strlen(input));//writes n bytes into socket
                break;
//case for help.
            case QM_:
            case HELP_:
                if (strcmp(arg1, "") != 0)
                    prnt_cmd_help(arg1);//print command help for argument1.
                else
                    prnt_cmd_list();//print the list of commands.
                printf("\n");
                goto noServer;

//case for lcd command.
            case LCD_:
                if (!new_dir(arg1))
                    fprintf(stderr, "local: %s:%s\n",arg1, strerror(errno));
                goto noServer;//go to noServer.

//case for open command.
            case OPEN_:
                fprintf(stderr, "Already connected to %s, use close first.", saddr);
                goto noServer;

            case ZERO_:
		goto noServer;

	    default:
                printf(INV_CMD);
                goto noServer;
        }


        //reads a line from socket
        if (Readline(sockfd, recv, CMAXLINE) == 0) {
            fprintf(stderr, "str_cli: server terminated prematurely\n");
            //      fflush(stdout);
            exit(1);
        }

        //setting the last character to null character
        recv[strlen(recv) - 1] = 0;

        //extract from recv errArg and display.
        sscanf(recv, "%[^:]:%[^:]", errArg, display);
        errno = atoi(errArg);//extracting the errno.

        //if errno is zero.
        if (errno == 0)
            Fputs(display, stdout);//putting the contents of string on to stdout
        else
            printf("%s", strerror(errno));

        printf("\n");

        //noServer starts from here.
        noServer:;
        printf(PRMT);
    }
    endWhile:;
    return false;
}
