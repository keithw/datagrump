#include <stdio.h>
#include <unistd.h>

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

  Address destination( ip, port );

  fprintf( stderr, "Sending packets to %s:%d.\n",
	   destination.ip().c_str(), destination.port() );

  Network::Socket sock;

  uint64_t sequence_number = 0;

  while ( 1 ) {
    Packet x( destination, sequence_number );

    sock.send( x );	       

    sleep( 1 );
  }

  return 0;
}
