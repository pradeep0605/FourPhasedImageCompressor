#include<iostream>
#include<fstream>
#include<bitset>

using namespace std;

bitset <8> toBits(unsigned char ch)
{
   return bitset<8>(ch);
}

unsigned char toChar(bitset <8> b)
{
  short ch=0;
  for(int i=7;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return ((unsigned char)ch);
}

unsigned int  toInt(bitset <24> b)
{
   unsigned int ch=0;
   for(int i=23;i>=0;i--)
   {
      ch=ch<<1;
      ch=ch+ (unsigned int)(b[i]);
   }
   return ch;
}

