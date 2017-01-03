#include<fstream>
#include<iostream>
#include "bitset.cpp"
#include "color.cpp"
#include<cstdlib>

using namespace std;

void firstPhase(char *s)
{
    char arr[56];
    unsigned int width=0, height=0;
    ifstream in(s,ios::binary);
    ofstream out("firstPhase.bmp",ios::binary);
    
    in.seekg(0,ios::end);
    int fileSize=in.tellg();
    in.seekg(0,ios::beg);
    in.seekg(18,ios::beg);
    in.read((char*) &width, 4);
    in.read((char*) &height, 4);
    in.seekg(0,ios::beg);
    in.read((char*)arr,54);
    out.write((char*)arr,54);
    fileSize-=54;
    color c1,c2,c3,c4,res;
    color carr1[width+1], carr2[width+1];
    
    for(unsigned int i=0;i<height;i+=2)
    {	
    	 in.read((char*) carr1,width*3);
    	 in.read((char*) carr2,width*3); 
    	 for(unsigned int j=0;j<width;j+=2)
    	 {	
    	 	c1=carr1[j];
    	 	c2=carr1[j+1];
    	 	
    	 	c3=carr2[j];
    	 	c4=carr2[j+1];
    	 	
    	 	res.red= (c1.red + c2.red + c3.red + c4.red )/4;
     	 	res.green= (c1.green + c2.green + c3.green + c4.green )/4;
    	 	res.blue= (c1.blue + c2.blue + c3.blue + c4.blue )/4;
    	 	out.write((char*) &res, 3);
    	 }
    }
    out.close();
}




