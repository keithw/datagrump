#include <cassert>

#include "address.hh"
#include "packet.hh"
#include "timestamp.hh"

using namespace std;
using namespace Network;

static const uint64_t PACKET_SIZE = 1480;

/* Make outgoing data packet */
Packet::Packet( const Address & addr, const uint64_t sequence_number )
  : addr_( addr ),
    sequence_number_( sequence_number ),
    send_timestamp_(),
    ack_sequence_number_( -1 ),
    ack_send_timestamp_(),
    ack_recv_timestamp_(),
    recv_timestamp_()
{
  assert( !is_ack() );
}

/* Make ACK */
Packet::Packet( const Address & addr, const uint64_t sequence_number,
		const uint64_t ack_sequence_number,
		const uint64_t ack_send_timestamp,
		const uint64_t ack_recv_timestamp )
  : addr_( addr ),
    sequence_number_( sequence_number ),
    send_timestamp_(),
    ack_sequence_number_( ack_sequence_number ),
    ack_send_timestamp_( ack_send_timestamp ),
    ack_recv_timestamp_( ack_recv_timestamp ),
    recv_timestamp_()
{
  assert( is_ack() );
}

/* Make incoming packet from wire */
Packet::Packet( const Address & addr, const std::string & str,
			 const struct timespec & receive_ts )
  : addr_( addr ),
    sequence_number_( str.substr( 0*sizeof( uint64_t ), sizeof( uint64_t ) ) ),
    send_timestamp_( str.substr( 1*sizeof( uint64_t ), sizeof( uint64_t ) ) ),
    ack_sequence_number_( str.substr( 2*sizeof(uint64_t), sizeof(uint64_t) ) ),
    ack_send_timestamp_( str.substr( 3*sizeof(uint64_t), sizeof(uint64_t) ) ),
    ack_recv_timestamp_( str.substr( 4*sizeof(uint64_t), sizeof(uint64_t) ) ),
    recv_timestamp_( timestamp( receive_ts ) )
{
  if ( str.size() != PACKET_SIZE ) {
    throw string( "Invalid packet size." );
  }
}

/* Prepare to send */
void Packet::set_send_timestamp( void )
{
  /* Fill in send timestamp */
  send_timestamp_ = Integer64( timestamp() );  
}

/* Make wire representation of packet */
std::string Packet::str( void ) const
{
  return sequence_number_.str()
    + send_timestamp_.str()
    + ack_sequence_number_.str()
    + ack_send_timestamp_.str()
    + ack_recv_timestamp_.str();
}
