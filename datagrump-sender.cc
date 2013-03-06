#include <stdio.h>

#include "socket.hh"

using namespace Network;

int main( int argc, char *argv[] )
{
  /* check arguments */
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s IP PORT\n", argv[ 0 ] );
    exit( 1 );
  }

  char *ip = argv[ 1 ];
  uint16_t port = atoi( argv[ 2 ] );

  fprintf( stderr, "Connecting to %s:%d...\n", ip, port );

  Network::Socket sock;
  sock.connect( Address( ip, port ) );

  return 0;
}
