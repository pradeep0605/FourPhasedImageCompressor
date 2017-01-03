#include<iostream>
#include<fstream>

using namespace std;


class Table
{
   public:
   unsigned int indicesSize;
   unsigned short  *indexes;
   unsigned int   *arr;
   unsigned int   no_bytes;
   Table()
   {
      indicesSize=0;
      no_bytes=0;
   }

   Table(int size)
   {
     indexes=new unsigned short[size];
     arr=new unsigned int[size];
   }

   Table(unsigned int *,unsigned short *,unsigned int,unsigned int);
   
   void display();
   void writeToFile(ofstream &out);
   void readFromFile(ifstream &in);
};

   void Table::writeToFile(ofstream &out)
   {
       out.write((char *) &indicesSize,sizeof(indicesSize));
       out.write((char *)   indexes, indicesSize*sizeof(unsigned short));
       out.write((char *)       arr, indicesSize*sizeof(unsigned int));
       out.write((char *) &no_bytes,sizeof(no_bytes));
   } 
   
   void Table::readFromFile(ifstream &in)
   {
       in.read((char *) &indicesSize,sizeof(indicesSize));
       in.read((char *)   indexes, indicesSize*sizeof(unsigned short));
       in.read((char *)       arr, indicesSize*sizeof(unsigned int));
       in.read((char *) &no_bytes,sizeof(no_bytes));
   }
   
   
Table::Table(unsigned int a[],unsigned short c[],unsigned int arraySize,unsigned int no_bytes)
{
   arr=new unsigned int	[arraySize];
   indexes=new unsigned short[arraySize];
   indicesSize=(unsigned int)arraySize;
   this->no_bytes=no_bytes;
     
   for(int i=0;i<arraySize;i++)
   {
      arr[i]=a[i];
      indexes[i]=c[i];
   }  
}


void Table:: display()
{
   cout<<"Size:"<<indicesSize<<endl;
   for(int i=0;i<indicesSize;i++)
   {
      cout<<"|"<<int(indexes[i])<<","<<arr[i];
   } 
    cout<<endl<<"No.bytes:"<<no_bytes<<endl;
}



class Table2
{    
   public:
   unsigned short indicesSize;
   unsigned char  *indexes;
   unsigned int   *arr;
   unsigned int   no_bytes;
   Table2()
   {
      indicesSize=0;
      no_bytes=0;
   }

   Table2(int size)
   {
     indexes=new unsigned char[size];
     arr=new unsigned int[size];
   }

   Table2(unsigned int *,unsigned char *,unsigned int,unsigned int);
   
   void display();
   void writeToFile(ofstream &out);
   void readFromFile(ifstream &in);
};

   void Table2::writeToFile(ofstream &out)
   {
       out.write((char *) &indicesSize,sizeof(indicesSize));
       out.write((char *)   indexes, indicesSize*sizeof(unsigned char));
       out.write((char *)       arr, indicesSize*sizeof(unsigned int));
       out.write((char *) &no_bytes,sizeof(no_bytes));
   } 
   
   void Table2::readFromFile(ifstream &in)
   {
       in.read((char *) &indicesSize,sizeof(indicesSize));
       in.read((char *)   indexes, indicesSize*sizeof(unsigned char));
       in.read((char *)       arr, indicesSize*sizeof(unsigned int));
       in.read((char *) &no_bytes,sizeof(no_bytes));
   }
   
   
Table2 ::Table2(unsigned int a[],unsigned char c[],unsigned int arraySize,unsigned int no_bytes)
{
   arr=new unsigned int[arraySize];
   indexes=new unsigned char[arraySize];
   indicesSize=(unsigned short)arraySize;
   this->no_bytes=no_bytes;
     
   for(int i=0;i<arraySize;i++)
   {
      arr[i]=a[i];
      indexes[i]=c[i];
   }  
}


void Table2:: display()
{
   cout<<"Size:"<<indicesSize<<endl;
   for(int i=0;i<indicesSize;i++)
   {
      cout<<"|"<<int(indexes[i])<<","<<arr[i];
   } 
    cout<<endl<<"No.bytes:"<<no_bytes<<endl;
}

