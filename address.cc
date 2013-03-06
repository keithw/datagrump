#include <stdio.h>
#include <arpa/inet.h>

#include "address.hh"

using namespace std;
using namespace Network;

/* Construct address from IP address and port number */
Address::Address( const string ip, const uint16_t port )
  : sockaddr_()
{
  sockaddr_.sin_family = AF_INET;
  sockaddr_.sin_port = htons( port );

  if ( inet_aton( ip.c_str(), &sockaddr_.sin_addr ) == 0 ) {
    fprintf( stderr, "Invalid IP address (%s)\n", ip.c_str() );
    exit( 1 );
  }
}

/* Get underlying IP address */
std::string Address::ip( void ) const
{
  char tmp[ 64 ];
  snprintf( tmp, 64, "%s", inet_ntoa( sockaddr_.sin_addr ) );
  return string( tmp );
}

/* Render address to string */
const string Address::str( void ) const
{
  char tmp[ 64 ];
  snprintf( tmp, 64, "%s:%d", inet_ntoa( sockaddr_.sin_addr ),
	    ntohs( sockaddr_.sin_port ) );
  return string( tmp );
}

