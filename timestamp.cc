#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <string>

#include "timestamp.hh"

using namespace std;
using namespace Network;

/* nanoseconds per second */
static const uint64_t BILLION = 1000000000;

uint64_t Network::timestamp( void )
{
  struct timespec ts;

  if ( clock_gettime( CLOCK_REALTIME, &ts ) < 0 ) {
    perror( "clock_gettime" );
    throw string( "clock_gettime error" );
  }

  return ts.tv_sec * BILLION + ts.tv_nsec;
}

uint64_t Network::timestamp( const struct timespec & ts )
{
  return ts.tv_sec * BILLION + ts.tv_nsec;
}
