/*******************************************************************
NAME       : DINESH SANDADI
ASSIGNMENT : 5
DUE DATE   : 4/28/2017
PURPOSE    : SERVER WRAPPER SOURCE CODE
Function   : This Contains definitions of 
	     various wrapper functions.
Wrapper Function : It is the function which is used for checking if
any errors occured in calling system call and how to handle them
i.e., whether to exit from program ot continue.
********************************************************************/

#include "wrap5srv.h"

bool servExitFlags[SNFLAGS + 1] = {false};

/*
Chdir Wrapper Function.
Arguments    : path that specifies the directory path
Return Value : integer that represents whether the command was successful or not.
 */
int Chdir(const char *path) {
    errno = 0;

    int determiner = chdir(path);
    if (determiner < 0) {

        if (servExitFlags[CHDIR])
            exit(CHDIR);
    }

    return determiner;
}

/*
Getcwd Wrapper function
Arguments    : buf to get the current working directory, size is size of the buffer.
Return value : return the current working directory.
*/
char *Getcwd(char *buf, size_t size) {
    errno = 0;

    char *determiner = getcwd(buf, size);
    if (determiner == NULL) {

        if (servExitFlags[GETCWD])
            exit(GETCWD);
    }
    return determiner;
}

/*
Signal wrapper function.
*/
Sigfunc *Signal(int signo, Sigfunc *func) {
    errno = 0;

    Sigfunc *determiner = signal(signo, func);

    if (determiner == SIG_ERR) {
        perror("Signal Failure");

        if (servExitFlags[SIGNAL]) exit(SIGNAL);
    }

    return determiner;
}

/*
  Readline() wrapper function definition
  fd     : file descriptor
  vptr   : variable ponter
  maxlen : length to be read 
*/

ssize_t Readline(int fd, void *vptr, size_t maxlen) {
    errno = 0; //resetting errno

    int determiner = readline(fd, vptr, maxlen);

    if (determiner < 0) {
        perror("Error in reading");
        if (servExitFlags[READLINE])
            exit(READLINE);
    }

    return determiner;
}

/*
  Fork() wrpper function definition
  No arguments 
  Purpose : This fucniton creates a child process  
*/
pid_t Fork(void) {
    errno = 0;//resetting

    pid_t processIdValue = fork();//creates a new child process

    if (processIdValue < 0) {
        perror("Can't fork the process");

        if (servExitFlags[FORK])
            exit(FORK);
    }

    return processIdValue;
}

/*
  Wait() wrapper function definition
  status :status of the process
  Purpose :This function makes parent process to wait for the child process to exit.
*/
pid_t Wait(int *status) {
    errno = 0;

    pid_t finalStatus = wait(status);

    if (finalStatus < 0) {
        perror("Error in waiting");

        if (servExitFlags[WAIT])
            exit(WAIT);
    }
    return finalStatus;
}

/*
  Fgets() wrapper function definition
  s     : string to be written the data into 
  size  : Number of bytes to read
  stream: stream to be read from 
*/

char *Fgets(char *s, int size, FILE *stream) {
    errno = 0;

    char *value = fgets(s, size, stream);

    //value null alone can't determine failure in systemcall it should be checked along with ferror()
    if ((value == NULL) && ferror(stream)) {
        perror("Error in Reading File");

        if (servExitFlags[FGETS])
            exit(FGETS);
    }
    return value;
}

/*
  Socket() wrapper function defintion
  domain   : internet protocol (IPV4 or IPV6)
  type     : transport protocol( TCP or UDP)
  protocol : this number is usually zero except when there are multiple protocols possible for particular domain and type
*/

int Socket(int family, int type, int protocol) {

    errno = 0;                //resetting errno to zero

    int determiner = socket(family, type, protocol);

    if (determiner < 0)            //if determiner is negative
    {
        perror("Socket is not created");

        if (servExitFlags[SOCKET])    //if flag is set then exit
            exit(SOCKET);

    }

    return determiner;

}

/*
  Function  : Bind(int,const struct sockaddr* , socklen_t)
  Arguments : 
  sockfd:socket file descriptor
  sockaddr* : pointer to the socket address structure
  addrlen   : length of socket address structure
*/
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {

    errno = 0;                        //setting errno to zero

    int r_value;                    //return value

    if ((r_value = bind(sockfd, addr, addrlen)) < 0)    //if return value is negative then system error
    {
        perror("can't bind socket to local address");

        if (servExitFlags[BIND])
            exit(BIND);

    }
    return r_value;

}

/*
  Function :Listen (int ,int)
  Purpose  :To make socket listen on particular port
  Arguments :
  sockfd  : socket file descriptor
  backlog : length of queue  
*/
int Listen(int sockfd, int backlog) {

    errno = 0;//setting errno to zero

    int r_value;

    if ((r_value = listen(sockfd, backlog)) < 0)//if return value is negative
    {
        perror("Error in listening");

        if (servExitFlags[LISTEN])        //if flag is set
            exit(LISTEN);

    }
    return r_value;

}

/*
  Function : Accept(int, struct sockaddr * ,socklent_t * )
  purpose  : To accept the client request and create a new socket
  Arguments :
  sockfd  : socket file descriptor
  addr    : pointer to sockaddr structure
  addrlen : pointer to the socklent_t  
*/
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {

    errno = 0;                    //sets errno to zero

    int fd = accept(sockfd, addr, addrlen);    //returns newly created socket file descriptor

    if (fd < 0)                    //if file descriptor is negative
    {
        if (errno == EINTR) Accept(sockfd, addr, addrlen);

        else {
            perror("can't accept the request");

            if (servExitFlags[ACCEPT])            //if flag is set then exit
                exit(ACCEPT);
        }
    }

    return fd;
}

/*
  Function : write(int ,const void *,size_t )
  purpose  : to write the data into socket
  Arguments: 
  fd   : filedescriptor
  buf  : pointer to the application buffer
  count: size of the data to copy 
*/
ssize_t Writen(int fd, const void *buf, size_t count) {

    errno = 0;                    //set errno to zero

    ssize_t r_value;

    //  printf("Still Waiting");
    if ((r_value = writen(fd, buf, count)) < 0)    //if return value is negative
    {
        perror("can't write in to socket");

        if (servExitFlags[WRITEN])//if exit flag is set
            exit(WRITEN);

    }

    return r_value;
}

/*
  Function : close(int ) 
  purpose  : to close the file with file descriptor fd
*/
int Close(int fd) {

    errno = 0;//setting errno to zero

    int r_value;

    if ((r_value = close(fd)) < 0) //if return value is negative
    {
        perror("can't close file");

        if (servExitFlags[CLOSE])//if exit flag is set
            exit(CLOSE);
    }

    return r_value;
}
