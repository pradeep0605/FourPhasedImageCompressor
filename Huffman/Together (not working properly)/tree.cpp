#include<iostream>
#include "huffstring.cpp" 

#define null 0

using namespace std;

class node
{
   public:
   unsigned int value;
   unsigned short ch;
   node * lchild, * rchild;
   
   node()
   {
     ch=0;
     value=0;
     lchild=rchild=null;
   }
   
   node(unsigned int value,unsigned short ch)
   {
      this->value=value;
      this->ch=ch;
      lchild=null;
      rchild=null;
   }
   
   node(node &n)
   {
      value=n.value;
      ch=n.ch;
      lchild=n.lchild;
      rchild=n.rchild;
   }
   
};




char *codeGen=new char[50];
int codeIndex=0;


void clearCodes()
{
   for(int i=0;i<50;i++)
      codeGen[i]='\0';
      
      codeIndex=0;
}

void generateCodes(node *root,String *codes)
{
   if(root->lchild!=null)
   {
     codeGen[codeIndex]='0';
     codeIndex++;
     generateCodes(root->lchild,codes);
   }
   
   if(root->rchild!=null)
   {
     codeGen[codeIndex]='1';
     codeIndex++;
     generateCodes(root->rchild,codes);
   }
   
   if(root->lchild==null && root->rchild==null)
   {
      //cout<<root->ch<<endl;
      codes[(unsigned int)root->ch]=codeGen;
   }
   
    codeGen[codeIndex]='\0';
    codeIndex--;   
}


void postOrder(node *root)
{
   if(root->lchild!=null)
   {
      postOrder(root->lchild);
   }
   
   if(root->rchild!=null)
   { 
      postOrder(root->rchild);
   }
   
   cout<<root->ch<<",   ";
}






