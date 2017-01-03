#include<iostream>

using namespace std;


class color
{
   public:
   unsigned char blue,green,red;
   color()
   {
       red=green=blue=0;
   }

   color operator /(int a)
   {
     color c;
     c=*this;
     c.red=c.red/a;
     c.green=c.green/a;
     c.blue=c.blue/a;
     return c;
   }

    color operator *(int a)
   {
     color c;
     c=*this;
     c.red=char(int(c.red)*a);
     c.green=char(int(c.green)*a);
     c.blue=char(int(c.blue)*a);
     return c;
   }
   
    color operator +(int a)
   {
     color c;
     c=*this;
     c.red=char(int(c.red+a));
     c.green=char(int(c.green+a));
     c.blue=char(int(c.blue+a));
     return c;
   }
  
   
   
   color operator -(color &c2)
   {
      color temp=color();
      temp.red=char(int(red-c2.red));
      temp.green=char(int(green-c2.green));
      temp.blue=char(int(blue-c2.blue));
       return temp;
   }

  int mod(int a)
   {
      if(a<0)
	 return (-1*a);
      else
	 return a;
   }

   int operator ==(color c)
   {
      int diff=3;
      int f1=0,f2=0,f3=0;
      int avg=0;

       if(mod(c.red-red)<=diff )
	f1=1;

      if(mod(c.green-green)<=diff )
	f2=1;

      if(mod(c.blue-blue)<=diff )
	f3=1;

      avg=int(int(f1+f2+f3)/3);

      if(avg==1)
      {
	return 1;
      }
      else
	return 0;
   }

   void display()
   {
    cout<<"red:"<<(int)red<<",  Green:"<<(int)green<<",  Blue:"<<(int)blue<<endl;
   }
};





