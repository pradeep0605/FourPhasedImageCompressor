/*THis program includes 

    This string class is mainly used for huffman coding "only"
*/

#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

class String
{

  public:
    char *str;                    		 //Character array

     String()
     {
       str=new char[1];
       str[0]='\0';
     }
     
     //constructor which constructs(memory allocation) the string with the specified no of character size.
     String(int size)
     {
       str=new char[size+5];
       str[0]='\0';
     }
     
     //Constructor what takes String literals to construct the object. 
     String(char *s)
     {
       str=new char[strlen(s)+5];
       strcpy(str,s);
     }
     
     int getLength()
     {
        return strlen(str);
     }
}; 
