#include <stdio.h>
#include <unistd.h>
#include <string>

#include "socket.hh"

using namespace std;
using namespace Network;

int main( int argc, char *argv[] )
{
  /* check arguments */
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s IP PORT\n", argv[ 0 ] );
    exit( 1 );
  }

  try {
    /* Fill in destination address from command line arguments */
    Address destination( argv[ 1 ] /* ip */, argv[ 2 ] /* port */ );

    fprintf( stderr, "Sending packets to %s:%d.\n",
	     destination.ip().c_str(), destination.port() );

    /* Create UDP socket for outgoing datagrams. */
    Network::Socket sock;

    /* Loop */
    uint64_t sequence_number = 0;
    while ( 1 ) {
      Packet x( destination, sequence_number++ );
      sock.send( x );
      sleep( 1 );
    }
  } catch ( const string & exception ) {
    /* We got an exception, so quit. */
    fprintf( stderr, "Exiting on exception: %s\n", exception.c_str() );
    exit( 1 );
  }

  return 0;
}
