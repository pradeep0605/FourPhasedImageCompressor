#include<bitset>
#include "string.cpp"


//Beggining of 5bit bitset <==> string
String to5String(bitset <5> b)
{
   String temp=String();
   for(int i=0;i<5;i++)
   {
      temp.str[4-i]=char(b[i]+48);
   }
   temp.str[5]='\0';
   return temp;
}

bitset <5> to5Bits(String &s)
{
    bitset <5> b;
    for(int i=0;i<5;i++)
    {
       b[4-i]= int(s.str[i])-48;
    }
    return b;
}


unsigned char toChar(bitset <5> b)
{
  short ch=0;
  for(int i=4;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return( (unsigned char)ch);
}

//========================================================================================================================




//Beggining of 3bit bitset <==> string
String to3String(bitset <3> b)
{
   String temp=String();
   for(int i=0;i<3;i++)
   {
      temp.str[2-i]=char(b[i]+48);
   }
   temp.str[3]='\0';
   return temp;
}

bitset <3> to3Bits(String &s)
{
    bitset <3> b;
    for(int i=0;i<3;i++)
    {
       b[2-i]= int(s.str[i])-48;
    }
    return b;
}

unsigned char toChar(bitset <3> b)
{
  short ch=0;
  for(int i=2;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return( (unsigned char)ch);
}

//========================================================================================================================



//Beggining of 1bit bitset <==> string
String to1String(bitset <1> b)
{
   String temp=String();
      temp.str[0]=char(b[0]+48);
   temp.str[1]='\0';
   return temp;
}

bitset <1> to1Bits(String &s)
{
    bitset <1> b;
       b[0]= int(s.str[0])-48;
    return b;
}


unsigned char toChar(bitset <1> b)
{
  short ch=0;
  if(b[0]==0)
    return( (unsigned char)ch);
  else
  {
    ch=1;
    return( (unsigned char)ch);
  }
}

//========================================================================================================================




//Beggining of 8bit bitset <==> string
unsigned char toChar(bitset <8> b)
{
  short ch=0;
  for(int i=7;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return( (unsigned char)ch);
}


String toString(bitset <8> b)
{
   String temp=String();
   for(int i=0;i<8;i++)
   {
      temp.str[7-i]=char(b[i]+48);
   }
   temp.str[8]='\0';
   return temp;
}

bitset <8> toBits(String &s)
{
    bitset <8> b;
    for(int i=0;i<8;i++)
    {
       b[7-i]= int(s.str[i])-48;
    }
    return b;
}


//========================================================================================================================



























