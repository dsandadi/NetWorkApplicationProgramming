/*************************************************************
Name       : Dinesh Sandadi
Assignment : 3
DueDate    : 3/10/2017
Purpose    : server program that accepts the client requests and 
	     sends the name of the author of text book requested by client.
             
Function   : This program does the following steps
1) Creates Socket ,assign optional port number if given else sets
   to default port
2) Fills the socket address structure
3) Binds the socket to particular port address, listens on that port
4) Accept the request from client and create another socket to handle that particular request 
5) writes data to socket from application buffer.Finally closes the socket. 
 ***************************************************************/

#include"wrap3srv.h"

extern bool servExitFlags[];

void setServExitFlags() {

    for (int i = 0; i < SNFLAGS + 1; i++)
        servExitFlags[i] = true;
}

int main(int argc, char *argv[]) {
    pid_t pid;
    //    char buff[MAXLINE];				//Application buffer
    unsigned int port_number = SERV_PORT;    //assigning port number to default port number

//if argument count is 2 then assign second argument to portnumber.
    if (argc == 2)
        port_number = atoi(argv[1]);        //a to i converts string to integer.

//if argument count is greater than 2 then print error
    if ((argc > 2)) {
        fprintf(stderr, "Usage:<Port number>");
        exit(500);
    }

    setServExitFlags();

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);    //wrapper call to create a socket

    struct sockaddr_in servaddr;            //declaring the socketaddress structure
    servaddr.sin_family = AF_INET;            //filling in the structure family to be IPV4
    servaddr.sin_port = htons(port_number);        //converts portnumber to network byte order
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//This makes the server to accept client connections from multiple interfaces.

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));    //wrapper to bind socket to particular port address

    Listen(listenfd, LISTENEQ);                //wrapper to listen

    Signal(SIGCHLD, handler);
    
    while (true) {
        int connfd = Accept(listenfd, NULL, NULL);    //wrapper to call accept,which accepts the client request
        //creates a child process
        
	if ((pid = Fork()) == 0) {//job is assigned to child
            Close(listenfd);//closes the listening socket
           
	    str_author(connfd);//perform the intended task
           
	    Close(connfd);//closes the socket
            exit(0);//exit successfully
        }
        
	Close(connfd);                    //wrapper to close connfd socket
    }
    
	Close(listenfd);
	exit(0);
}

/*****************************************
Function :handler
Purpose  : This function is called when ever
	   a signal is received by process 
	   from kernel.
******************************************/

void handler(int signo)
{   
	Wait(0);//calls Wait wrapper function
        signal(SIGCHLD,handler);//activating the signal again

}

/***********************************************************
Function   : void str_author()
Arguments  : int
Return type: void
Purpose    : This function reads from the socket line by line 
	     and seraches for the author of requested book,
	     and sends the client author name.
**************************************************************/
void str_author(int connfd) {
    FILE *pFile;//creating a pointer to the file

    //variable declaration
    char mystring[SIZE];
    char title[SIZE];
    char author[SIZE];
    char input[SIZE];
    pFile = Fopen(DATAPATH, "r");

    int size = 0;

	//while loop to read from socket line by line
    while ((size = Readline(connfd, input, SMAXLINE)) > 0) {
        int found = 0;
        input[strlen(input) - 1] = 0;
	
	/* logic for finding author name from the data base
         * */
        Fseek(pFile, 0, SEEK_SET);//set the pointer to the begining of the file

        while ((Fgets(mystring, SMAXLINE , pFile)) != NULL) {
            int i = 0;
            //to get the book name from the data base.
            while (mystring[i] != ':') {
                title[i] = mystring[i];
                i++;
            }//end of inner while
            title[i] = '\0';

            // comparing the input with the title

            if (strcasecmp(title, input) == 0) {
                found = 1;

                char *seekerTemp;	  //character pointer
                seekerTemp = mystring + i;//setting the pointer to the position where author name starts
                seekerTemp++;		  //increment the pointer
                int i = 0;
                //to store the author name in the string author
                while (seekerTemp[i] != ':') {
                    author[i] = seekerTemp[i];
                    i++;
                }//end of inner while

                //appending the characters.
                author[i] = '\n';
                author[i + 1] = '\0';
		
                break;
            }//end of if
        } //end of outer while
       
        //if not found copy unknown to the string
        if (found == 0) strncpy(author,"Unknown\n",SIZE);
      
        Writen(connfd, author, strlen(author));//writes the author name into the socket

    }
    Fclose(pFile);//closes the file

    return;
}

