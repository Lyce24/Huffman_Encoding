// Eriksen Liu
#include "bitio.hh"
#include <iostream>

using namespace std;

BitInput::BitInput(std::istream &is)
    : in(is), buf(0), nbits(8) // initialize the variables. (nbits = 8 because we what it to get a charactor at first)
{
}

bool BitInput::input_bit()
{
  // if we shift the buffer 8 times, then get a new character from in and store it in buffer, reset the counter (nbits)
  if (nbits == 8)
  {
    buf = in.get();
    nbits = 0;
  }
  // shift buffer right (7-nbits) to get the most siginificent figure (don't change the value of buffer), and with one to get its bool value
  bool val;
  val = buf >> (7 - nbits) & 1;
  // increase the counter (nbits)
  nbits++;
  // return the boolean value
  return val;
}

BitOutput::BitOutput(std::ostream &os)
    : out(os), buf(0), nbits(0) // initialize the variables
{
}

void BitOutput::output_bit(bool bit)
{
  // if we added 8 bits in the buffer, then put the buffer into out and reset buffer and counter (nbits)
  if (BitOutput::nbits == 8)
  {
    out.put(buf);
    buf = 0;
    nbits = 0;
  }
  // shift left one time to make space to store bit (new space always fills with a 0)
  buf = buf << 1;
  // or with bit to change the value of the last bit of buffer
  buf = buf | bit;
  // increase the counter
  nbits++;
  return;
}

BitOutput::~BitOutput()
{
  // if there are still spaces for buffer, then fill them then put the buffer into output
  while (nbits != 8)
  {
    // filled with trailing zeros
    buf = buf << 1;
    nbits++;
  }
  // put the extra buffer into out.
  out.put(buf);
}
