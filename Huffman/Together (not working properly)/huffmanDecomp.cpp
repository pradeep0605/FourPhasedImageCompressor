
/* For performance improvement I cant do the following things
  1. better sorting alogrith thatn quick sort.
  2. Or to eliminate sorting.
  3. Have least access to the hard disk as it increases the execution time.
  4. Remove as many couts as possible.
  5. Remove waste  code.
  */
#include<iostream>
#include<fstream>
#include "table.cpp"
#include "huffbitset.cpp"
#include "treeGenerator.cpp"

using namespace std;

unsigned long int bytesDetected=0;


void writeDecompressedCode(ofstream &,ifstream & ,/*String *,String *,*/unsigned int, node *,node *);

int main(int argc, char *argv[])
{  
     	
   if(argc<2)
   {
     cout<<"Improper arguments";
     return 0;
   }
   
   bytesDetected=0;
   
   ofstream out("decomp.rle",ios::binary);
        
    ifstream in(argv[1],ios::binary);
    char ar[56];
    in.read((char*)ar,54);
    out.write((char*)ar,54);
    int properCount=0;
    in.read((char*)&properCount,sizeof(int));
    
    in.seekg(-4,ios::cur);
    
   
    
    Table t=Table(properCount);
    Table2 t2=Table2(256);
    
    
    t.readFromFile(in);
    t2.readFromFile(in);
    //t.display();
    //t2.display();
    
    node *roots=new node[t.indicesSize];
    node *roots2=new node[t2.indicesSize];     
    
    for(int i=0;i<t.indicesSize;i++)
    {
       roots[i]=node( t.arr[i] , t.indexes[i]);
    }    
    
        
    for(int i=0;i<t2.indicesSize;i++)
    {
       roots2[i]=node( t2.arr[i] , t2.indexes[i]);
    }
        
   node *ROOT=constructTree(roots,t.indicesSize);
   node *ROOT2=constructTree(roots2,t2.indicesSize); 
   
   
   /*postOrder(ROOT);
   cout<<endl<<endl;
   postOrder(ROOT2);*/
   
   String *code=new String[32769];
   String *code2=new String[256];
   
   clearCodes();
   generateCodes(ROOT,code);
   clearCodes();
   generateCodes(ROOT2,code2);
   
   
   for(int i=0;i<32768;i++)
   {
       if(code[i].getLength()>0)
       {
          cout<<i<<"\t\t"<<code[i].str<<endl;
       }
   }
   cout<<"=========================================================="<<endl;
   for(int i=0;i<256;i++)
   {
      if(code2[i].getLength()>0)
      {
          cout<<i<<"\t\t"<<code2[i].str<<endl;
      }
   }
   
   
  
   
   writeDecompressedCode(out,in,/*code,code2,*/t.no_bytes,ROOT,ROOT2);
   cout<<endl<<"Bytes Detected:"<<bytesDetected;
   
   return 0;
}


String toString(bitset <8> b)
{
  String temp(10);
  for(int i=0;i<8;i++)
  {
    temp.str[i]= (unsigned char) (b[7-i] +48);
  }
  return temp;
}



String toString(bitset <16> b)
{
  String temp(50);
  for(int i=0;i<16;i++)
  {
    temp.str[i]= (unsigned char) (b[15-i] +48);
  }
  return temp;
}


int getDecompressedShort(String &s,node *ROOT)
{
   node *temp;
   temp=ROOT;
   int k=0;
   
   while(s.getLength()>0)
   {
        if(temp->lchild == null && temp->rchild==null)
        {  
           strcpy(s.str,&(s.str[k]));
           bytesDetected+=3;
           return ((unsigned int) temp->ch);
        }  
        else
        {
           if(s.str[k]=='\0')
                return -1;
                
           if(s.str[k]=='0')
           {
              temp=temp->lchild;
              k++;
           }
           else
           {
              temp=temp->rchild;
              k++;
           }
        }  
      
   }
   return -1;
}


int getDecompressedChar(String &s,node *ROOT)
{
   node *temp;
   temp=ROOT;
   int k=0;
   
   while(s.getLength()>0)
   {
        if(temp->lchild == null && temp->rchild==null)
        {  
           strcpy(s.str,&(s.str[k]));
           bytesDetected++;
           return ((unsigned int) temp->ch);
        }  
        else
        {
           if(s.str[k]=='\0')
                return -1;
                
           if(s.str[k]=='0')
           {
              temp=temp->lchild;
              k++;
           }
           else
           {
              temp=temp->rchild;
              k++;
           }
        }  
      
   }
   return -1;
}

void writeDecompressedCode(ofstream &out,ifstream &in ,/*String code[],String code2[],*/unsigned int nobytes, node *ROOT, node *ROOT2)
{
     unsigned short ch=0;
     unsigned char ch2=0,data=0;
     int i1=-1,i2=-1,i=0;
     String s( 100 );
     
     for(i=0;i<100;i++)
         s.str[i]='\0';
         
      bitset <8> b2;
      while(!in.eof() && nobytes>=3)
      {
          while(i1==-1 && !in.eof())
          {
             i1=getDecompressedShort(s,ROOT);
             in.read((char*)&data,1);
             
             b2=data;
             strcat(s.str,toString(b2).str);          
            
          }
          ch=i1;
          out.write((char*)&ch,2);
          nobytes-=2;
          while(i2==-1 && !in.eof())
          {
             i2=getDecompressedChar(s,ROOT2);
             in.read((char*)&data,1);
             b2=data;
             strcat(s.str,toString(b2).str);          
         }
         ch2=i2;
         out.write((char*)&ch2,1);
         nobytes-=1;
         //continue
      }
      while(s.getLength()>0 && nobytes>=3)
      {
         i1=getDecompressedShort(s,ROOT);
         ch=i1;
         out.write((char*)&ch,2);
         i2=getDecompressedChar(s,ROOT2);
         ch2=i2;
         out.write((char*)&ch2,1);
         nobytes-=3;         
      }
      out.flush();
}








