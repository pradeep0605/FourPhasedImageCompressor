
/* For performance improvement I cant do the following things
  1. better sorting alogrith thatn quick sort.
  2. Or to eliminate sorting.
  3. Have least access to the hard disk as it increases the execution time.
  4. Remove as many couts as possible.
  5. Remove waste  code.
  */
  
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include "huffbitset.cpp"
#include "treeGenerator.cpp"
#include "table.cpp"

using namespace std;


unsigned short toShort(bitset <16> b)
{
  unsigned short ch=0;
  for(int i=15;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return ch;
}

void writeCompressedCode(ofstream &,ifstream &,String *,String *,unsigned int);

int main(int argc, char *argv[])
{  
    setpriority(PRIO_PROCESS,0,-20);
   if(argc<2)
   {
     cout<<"Improper arguments";
     return 0;
   }
   unsigned char header[56];
   unsigned int *arr=new unsigned int [32768];
   unsigned int *arr2=new unsigned int[256];
   unsigned int fileSize=0;
   ifstream in(argv[1],ios::binary);
   ofstream out(strcat(argv[1],".pkr"),ios::binary);
   in.seekg(0,ios::end);
   fileSize=in.tellg();
   in.seekg(0,ios::beg);
   in.read((char*)header,54);
   out.write((char*)header,54);
   
   for(int i=0;i<32768;i++)
       arr[i]=0;
       
       
   for(int i=0;i<256;i++)
       arr2[i]=0;
   
   unsigned int temp=fileSize;
   temp-=54;
   
   unsigned short pixel=0;
   unsigned char  count=0;
   while(temp>2)
   {
       in.read((char*)&pixel,2);
       arr[pixel]++;
       in.read((char*)&count,1);
       arr2[count]++;
       temp-=3;
   }
   
   
   unsigned int properCount=0,properCount2=0;
   for(int i=0;i<32768;i++)
   {
      if(arr[i]>0)
         properCount++;
   }
   
   for(int i=0;i<256;i++)
   {
     if(arr2[i]>0)
           properCount2++;
   }
   
   cout<<endl<<"proper count:"<<properCount<<endl;
     
   
   node roots[properCount]; 
   node roots2[properCount2];
   
   int k=0;
   for(int i=0;i<32768;i++)
   {
      if(arr[i]>0)
      {
        roots[k]=node(arr[i],(unsigned short)i);                 
        k++;
      } 
   }
   
   k=0;
   for(int i=0;i<256;i++)
   {                         
     if(arr2[i]>0)                  
     {                                      
       roots2[k]=node(arr2[i],(unsigned short)i); 
       k++;                                        
     }                                        
   }                 
   
   node *ROOT=constructTree(roots,properCount);
   node *ROOT2=constructTree(roots2,properCount2);
   
   /*postOrder(ROOT);
   cout<<endl<<endl;
   postOrder(ROOT2);*/
 
    String *code=new String[32769];
   String *code2=new String[256];
   
   clearCodes();
   generateCodes(ROOT,code);
   clearCodes();
   generateCodes(ROOT2,code2);
   
   int compsize=0,originalsize=0;  
   for(int i=0;i<32768;i++)
   {
       if(code[i].getLength()>0)
       {
          compsize=compsize + (code[i].getLength()*arr[i]);
          originalsize=originalsize+(16*arr[i]);
   
          //cout<<i<<"\t\t"<<code[i].str<<"\t\t\t\t"<<arr[i]<<endl;
   
       }
   }
   cout<<"=========================================================="<<endl;
 
   for(int i=0;i<256;i++)
   {
      if(code2[i].getLength()>0)
      {
          compsize=compsize + (code2[i].getLength()*arr2[i]);
          originalsize=originalsize+(8*arr2[i]);
          //cout<<i<<"\t\t"<<code2[i].str<<"\t\t\t\t"<<arr2[i]<<endl;
      }
   }
   
  
   

 
   in.close();
   ifstream ins;
   ins.open(argv[1],ios::binary);
   ins.seekg(0,ios::beg);
   ins.read((char*)header,54);
   
     
   
   unsigned short indexes[properCount];
   unsigned int  array[properCount];
   k=0;
   for(int i=0;i<32768;i++)
   {
     if(arr[i]>0)
      {
          indexes[k]=(unsigned int)i;
          array[k]=arr[i];
          k++;
      }
   } 
   
   unsigned char indexes2[properCount2];
   unsigned int  array2[properCount2];
   k=0;
   for(int i=0;i<256;i++)
   {
     if(arr2[i]>0)
      {
          indexes2[k]=(unsigned char)i;
          array2[k]=arr2[i];
          k++;
      }
   }
    
     cout.flush();
   Table t=Table(array,indexes,properCount,(unsigned int)fileSize);
   Table2 t2=Table2(array2,indexes2,properCount2,(unsigned int)fileSize);
   t.writeToFile(out);
   t2.writeToFile(out);
   
   cout.precision(6);
   cout<<endl<<"Size of compressed data only="<<compsize<<"     "<<float(compsize)/(8*1024)<<" Kbytes"<<endl;
   cout<<endl<<"originalSize="<<originalsize+54<<"\tcompseize="<<(compsize + ((t.indicesSize*4) + (t.indicesSize*2) + (t2.indicesSize*4) + (t.indicesSize*1) + 14 + 54)*8 )<<endl;
   cout<<endl<<"originalSize="<<float(originalsize+54)/(8*1024)<<" Kbytes         compseize="<<float(compsize + ((t.indicesSize*4) + (t.indicesSize*2) + (t2.indicesSize*4) + (t.indicesSize*1) + 14 + 54)*8 )/(8*1024)<<" Kbytes"<<endl;
       
   //t.display();
   //t2.display();
   out.flush();
   //return 0;
   
   writeCompressedCode(out,ins,code,code2,fileSize);
  
   out.flush();
  
}



  void writeCompressedCode(ofstream &out,ifstream &in,String *code,String *code2,unsigned int Size)
  {
     Size-=54;
     unsigned short sh=0,data=0;
     unsigned writtenbytes=0,nobits=0;
     unsigned char ch=0;
     char finalcode[100];
     
     for(int m=0;m<100;m++)
         finalcode[m]='\0';
     bitset <16> b;
     while(Size>=3)
     {
         while( strlen(finalcode) <16 && Size>=3)
         {
              in.read((char*)&sh,sizeof(unsigned short));
              in.read((char*)&ch,sizeof(unsigned char));
              Size-=3;
              strcat(finalcode,code[sh].str);
              strcat(finalcode,code2[(int)ch].str);
              nobits=nobits+code[sh].getLength();
              nobits=nobits+code2[(int)ch].getLength();
              

         } 
         
         while(strlen(finalcode)>15)
         {
             for(int i=0;i<16;i++)
               b[15-i]=int(finalcode[i])-48 ;
              data=toShort(b);
             out.write((char*) &data,sizeof(unsigned short));               
            writtenbytes+=2;
           strcpy(finalcode,&(finalcode[16]));          
         }      
     }
       
              
         while(strlen(finalcode)>15)
         {
             for(int i=0;i<16;i++)
               b[15-i]=int(finalcode[i])-48 ;
             data=toShort(b);
             out.write((char*) &data,sizeof(unsigned short));                    
     
         writtenbytes+=2;
           strcpy(finalcode,&(finalcode[16]));          
         } 
         
         for(int i=0;i<strlen(finalcode);i++)
         {
             b[15-i]=int(finalcode[i])-48 ;
         }     
          data=toShort(b);
             out.write((char*) &data,sizeof(unsigned short));                           
            writtenbytes+=2;
           strcpy(finalcode,&(finalcode[16]));

           cout<<endl<<"Written bytes="<<writtenbytes<<endl;
           cout<<"no of detected bits="<<nobits<<"     "<<float(nobits)/(8*1024)<<" Kbytes"<<endl;
           out.flush();           
     
  }    
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
