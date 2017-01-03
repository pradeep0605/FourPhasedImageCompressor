#include "firstPhase.cpp"

using namespace std;


void secondPhase(char *s)
{
    ifstream in(s,ios::binary);
    in.seekg(0,ios::end);
    int fileSize=in.tellg();
    in.seekg(0,ios::beg);
    ofstream out("secondPhase.bmp",ios::binary);
    unsigned char arr[4097];
    in.read((char*)arr,54);
    out.write((char*)arr,54);
    fileSize-=54;
    color c;
    
    while(fileSize>2)
    {
       in.read((char*)&c,3);
       c=c/8;
       out.write((char*)&c,3);
       fileSize-=3;
    }
    /*while(fileSize>4095)
    {
        in.read((char*)arr,4096);
        for(int i=0;i<4096;i++)
        {
           arr[i]=char(int(arr[i]/8));   
        }
        out.write((char*)arr,4096);
       fileSize-=4096;
    }
    
    in.read((char*)arr,fileSize);
    for(int i=0;i<fileSize;i++)
    {
           arr[i]=char(int(arr[i]/8));   
    }
    out.write((char*)arr,fileSize);
    */    
    out.close();
}
