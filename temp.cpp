#include<iostream>
#include<bitset>
#include<fstream>
#include "color.cpp"

using namespace std;	

int main(int argc, char **argv)
{
    ifstream in(argv[1],ios::binary);
    short width=0, hieght=0;
    int count=54;
    ofstream out("test.bmp",ios::binary);
    /*while(count > 0)
    {
       in.read((char*)&sh,2);
       cout<<sh<<",    ";
       count-=2;
    } */
    
    in.seekg(18,ios::beg);  
       in.read((char*)&width,2);
    in.seekg(22,ios::beg);  
       in.read((char*)&hieght,2);
    in.seekg(0,ios::beg);
    
    char header[56];
    in.read((char*)header,54);
    out.write((char*)header,54);
    out.flush();
    
    color arr[width*2+1];
    color ch1,ch2,ch3,ch4;
    for(int i=0;i<hieght/2;i++)
    {
        in.read((char*)arr,sizeof(color) * width*2);
        
        for(int j=0;j<width;j=j+2)
        {
            ch1=arr[j];
            ch2=arr[j+1];
            ch3=arr[j+width];
            ch4=arr[j+width+1];
            ch1.red=(ch1.red+ch2.red+ch3.red+ch4.red)/4;
            ch1.green=(ch1.green+ch2.green+ch3.green+ch4.green)/4;       
            ch1.blue=(ch1.blue+ch2.blue+ch3.blue+ch4.blue)/4;
            
            arr[j]= arr[j+1]=   arr[j+width]=   arr[j+width+1]=ch1;
            
        }       
        out.write((char*)arr,sizeof(color) * width*2);
        out.flush();
    }
    out.close();   
    return 0;
}
