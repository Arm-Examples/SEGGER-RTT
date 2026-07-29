
#include <SEGGER_RTT.h>
#include <stdio.h>


uint8_t Buffer[ 32 ] = { "Foo" } ;

int main(void)
{
    SEGGER_RTT_Init( ) ;

    printf( "Please enter your name: " ) ;
    scanf( "%s", Buffer ) ;
    printf( "\nHello %s!\n", Buffer ) ;

    putchar( '\x04' ) ;  // Send EOT to terminate RTT session
    fflush(stdout) ;

    while( 1 )
    {
    }
}
