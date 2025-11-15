#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    
    //check arguments
    if ( argc != 2 ) {
        fprintf( stderr, "USAGE: parta FILEIN\n" ) ;
        return 1 ;
    }

    //open input file using low-level system call
    int fd = open( argv[ 1 ], O_RDONLY ) ;
    if ( fd < 0 ) {
        printf( "ERROR: %s not found\n", argv[ 1 ] ) ;
        return 2 ;
    }

    //counters 
    int upper = 0 ;
    int lower = 0 ;
    int digits = 0 ; 
    int space = 0 ; 
    int other = 0 ;

    //read file in bytes
    ssize_t bytes_read ;
    while ( ( bytes_read = read( fd, buffer, BUFSIZE ) ) > 0) {
        for ( ssize_t i = 0 ; i < bytes_read ; i++ ) {
            char c = buffer[i];

            if ( isupper( ( unsigned char )c ) ) {
                upper++ ;
            }
            else if ( islower( ( unsigned char )c ) ) {
                lower++ ;
            }
            else if ( isdigit( ( unsigned char )c ) ) {
                digits++ ;
            }
            else if ( isspace( ( unsigned char )c ) ) {
                space++ ;
            }
            else {
                other++ ;
            }
            
        }
    }

    //close file descriptor
    close( fd ) ;

    //prints the counts in desired format
    printf( "Upper,%d\n", upper ) ;
    printf( "Lower,%d\n", lower ) ; 
    printf( "Number,%d\n", digits ) ;
    printf( "Space,%d\n", space ) ;
    printf( "Other,%d\n", other ) ;

    return 0;
}
