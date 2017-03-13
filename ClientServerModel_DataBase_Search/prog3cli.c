/*************************************************************
Name       : Dinesh Sandadi
Assignment : 3
DueDate    : 3/10/2017
Purpose    : Client program that requests the server for author name
	     by optional port number.
Function   : This program does the following steps
1) Creates Socket ,assign optional port number if given else sets 
   to default port  
2) Fills the socket address structure
3) Connects to the server and writes data into socket, Retrieves data from server
4) Reads the data from socket to buffer and finally closes the socket.
 ***************************************************************/

#include"wrap3cli.h"//includes userdefined header for wrapper

extern bool exitFlag[];

/*
Function : setExitFlags() 
Purpose  : sets exitflags to determine whether to exit from program or not.
*/
void setExitFlags() {

    for (int i = 0; i < NFLAGS + 1; i++) {

        exitFlag[i] = true;

    }

}

int main(int argc, char **argv) {
    int sockfd;           //declaring file descriptor
    struct sockaddr_in address; //declaring address as sockaddress structure for IPV4
    unsigned int port_number;            //declaring port_number variable

    setExitFlags();             //calling setExitFlags () function

    if (argc != 3 && argc != 2) //if arguments are too few then exit from program
    {
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);//print message on stderror
        exit(55);                                           //exit
    }

    port_number = (argc == 2) ? SERV_PORT : atoi(argv[2]);
    //sets the port number to default port if no arguments are provides else sets it to provided argument

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);      //calling Socket wrapper function
    bzero(&address, sizeof(address));              //clearing the address structure
    address.sin_family = AF_INET;                  //setting the family to be of IPV4
    address.sin_port = htons(port_number);         //setting port number to optional value
    Inet_pton(AF_INET, argv[1], &address.sin_addr);//converts destination address to network byte order

    Connect(sockfd, (SA *) &address, sizeof(address));//calls Connect wrapper function

    //calls the function to request data from server
    str_cli(sockfd);

    Close(sockfd);//close socket file

    if (exitFlag[NOERROR])
        exit(NOERROR);                                    //exit successfully
}

/****************************************************
 * Function     : str_cli(int)
 * Return value : void
 * purpose      : Takes the book name from the
 *                stdin and sends it to the server
 *                , and also retrieves the author
 *                name from server
 ***************************************************/
void str_cli(int sockfd) {
    char recv[CMAXLINE + 1];     //declaring an application buffer to receive the data from socket
    char input[LENGTH];         // to write the data from application to socket

    fprintf(stdout, "Title of Book:");

    //while loop for accepting the input from user
    while ((Fgets(input, sizeof(input), stdin)) != NULL) {

        Writen(sockfd, input, strlen(input));//writes n bytes into socket

	//reads a line from socket
	if ( Readline ( sockfd, recv, CMAXLINE ) == 0 ) {
	  fprintf ( stderr, "str_cli: server terminated prematurely\n" );
	  exit ( 1 );
	}
	
        //setting the last character to null character
        recv[strlen( recv ) - 1] = 0;

        fprintf( stdout, " Author of Book: " );
        Fputs( recv, stdout );//putting the contents of string on to stdout
        fprintf( stdout, "\n\nTitle of Book:" );
    }
}
