#include <stdio.h>

#include "socket.hh"

using namespace Network;

int main( int argc, char *argv[] )
{
  /* check arguments */
  if ( argc != 2 ) {
    fprintf( stderr, "Usage: %s PORT\n", argv[ 0 ] );
    exit( 1 );
  }

  uint16_t port = atoi( argv[ 1 ] );

  fprintf( stderr, "Listening on %d...\n", port );

  Network::Socket sock;
  sock.bind( Address( "0", port ) );

  while ( 1 ) {
    Packet x = sock.recv();
    fprintf( stderr, "Got packet from %s (payload length = %u).\n",
	     x.addr().ip().c_str(), x.payload_len() );
  }

  return 0;
}
