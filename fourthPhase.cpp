#include "thirdPhase.cpp"

void copy(ifstream &in,ofstream &out, int length)
{
       char arr[1024];
       while(length>1023)
       {
          in.read((char*)arr,1024);
          out.write((char*)arr,1024);
          length-=1024;
       }   
       
      in.read((char*)arr,length);
      out.write((char*)arr,length);
      out.flush(); 
}
 
void fourthPhase(char *s)
{
        ofstream out (strcat(s,".pkr"),ios::binary);
        ifstream in1("header",ios::binary);
        ifstream in2("color.pkr",ios::binary);
        ifstream in3("count.pkr",ios::binary);
        char arr[56];
        int length=0;
        in1.read((char*)arr,54);
        out.write((char*)arr,54);
        
        in2.seekg(0,ios::end);
        length=in2.tellg();
        in2.seekg(0,ios::beg); 
        out.write((char*)&length,sizeof(int));
        
        copy(in2,out,length);
 
        
        in3.seekg(0,ios::end);
        length=in3.tellg();
        in3.seekg(0,ios::beg); 
 
        out.write((char*)&length,sizeof(int));
        
        copy(in3,out,length);
        
         
}
