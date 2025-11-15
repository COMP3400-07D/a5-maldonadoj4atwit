#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    
    //checks arguments
    if ( argc != 3 ) {
        fprintf( stderr, "USAGE: partb FILEIN FILEOUT\n" ) ;
        return 1 ;
    }

    char* input_filename = argv[ 1 ] ;
    char* output_filename = argv[ 2 ] ;

    //opens the output file
    int fd = open( output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770 ) ;
    if ( fd < 0 ) {
        perror( "ERROR: could not open output file" ) ;
        return 2 ;
    }

    //redirects STDOUT to the file
    if ( dup2( fd, STDOUT_FILENO ) < 0 ) {
        perror( "ERROR: dup2 failed" ) ;
        close( fd ) ;
        return 3 ;
    }
    // original fd no longer needed after dup2
    close(fd); 

    //prints the header and flush
    printf( "Category,Count\n" ) ;
    fflush( stdout ) ;

    //prepares arguments for execv for parta
    char* parta_args[] = { "./parta", input_filename, NULL } ;

    //execute parta
    int eret = execv( "./parta", parta_args ) ;

    //only if execv fails
    perror( "ERROR: execv failed" ) ;

    return 4 ;

}
