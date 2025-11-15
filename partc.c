#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    //checks for correct number of arguments
     if ( argc != 2 ) {
        printf( "USAGE: partc FILEIN\n" ) ;
        return 1 ;
    }

    //creates a pipe for interprocess communication
    int pipefd[ 2 ] ;
    if ( pipe( pipefd ) < 0 ) {
        perror( "pipe" ) ;
        return 1 ;
    }
    //forks a child process
    pid_t pid = fork() ;
    if ( pid < 0 ) {
        perror( "fork" ) ;
        return 1 ;
    }

    //parent process that runs parta
    if ( pid > 0 ) {

        close( pipefd[ 0 ] ) ; 

        dup2( pipefd[ 1 ], STDOUT_FILENO ) ;
        close( pipefd[ 1 ] ) ;

        char* args[] = { "./parta", argv[ 1 ], NULL } ;
        execv( "./parta", args ) ;

        perror( "execv parent" ) ;
        return 1 ;
    } 
    //child process that runs sort
    else {
        close( pipefd[ 1 ] ) ; 
        
        dup2( pipefd[ 0 ], STDIN_FILENO ) ;
        close( pipefd[ 0 ] ) ;

        //executes sort program:
        char* args[] = { "sort", "-t,", "-k2", "-n", NULL } ;
        execvp( "sort", args ) ;

        perror( "execvp child" ) ;
        return 1 ;
    }

    return 0;
}
