#include "byte_stream.hh"
#include <algorithm>

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  return is_closed_;
}

void Writer::push( string data )
{
  uint64_t sz = min( available_capacity(), data.size() );
  std::copy_n( data.begin(), sz, back_inserter( buffer_ ) );
  bytes_pushed_ += sz;
}

void Writer::close()
{
  is_closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  return is_closed_ && buffer_.size() == 0;
}

uint64_t Reader::bytes_popped() const
{
  return bytes_poped_;
}

string_view Reader::peek() const
{
  if ( buffer_.empty() )
    return {};
  return string_view { reinterpret_cast<const char*>( buffer_.data() ), buffer_.size() };
}

void Reader::pop( uint64_t len )
{
  uint64_t sz = min( len, buffer_.size() );
  buffer_.erase( buffer_.begin(), buffer_.begin() + sz );
  bytes_poped_ += sz;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}
