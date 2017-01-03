#include<iostream>
#include "bitset.cpp"
#include "color.cpp"
#include<cstdlib>

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

void firstPhaseDecomp()
{
        ifstream in1("header",ios::binary);
        ifstream in2("decompcolor",ios::binary);
        ifstream in3("decompcount",ios::binary);
        ofstream out("decomp.rle",ios::binary);
        char arr[56];
        in1.read((char*)arr,54);
        out.write((char*)arr,54);
        
        in2.seekg(0,ios::end);
        int size=in2.tellg();
        in2.seekg(0,ios::beg);
        
        unsigned short sh=0;
        unsigned char ch=0;
        while(size>1)
        {
           in2.read((char*)&sh,2);
           in3.read((char*)&ch,1);
           out.write((char*)&sh,2);
           out.write((char*)&ch,1);   
           size-=2;
        }
        
      out.flush();        
}

void secondPhaseDecomp(char *s)
{
    unsigned char arr[56];
    int filesize=0;
    ifstream in(s,ios::binary);
    in.seekg(0,ios::end);
    filesize=in.tellg();
    in.seekg(0,ios::beg);
    ofstream out("expand.bmp",ios::binary);
    in.read((char*)arr,54);
    out.write((char*)arr,54);
    filesize-=54;
    color c;
    unsigned char ch=0;
    unsigned short res=0;
    while(filesize>2)
    {   
    	res=0;
        in.read((char*)&res,sizeof(unsigned short));
        c.blue=(res%32)*8;
        res/=32;
        c.green=(res%32)*8;
        res/=32;
        c.red=res*8;
        
        in.read((char*)&ch,sizeof(unsigned char));
        filesize-=3;
       for(int i=0;i<(int)ch;i++)
       {
	out.write((char*)&c,sizeof(color));
       }
    }
    out.close();
   
}


void thirdPhaseDecomp( char *s)
{
    char arr[56];
    unsigned int width=0, height=0;
    ifstream in(s,ios::binary);
    ofstream out("finalOut.bmp",ios::binary);
    
    /*in.seekg(0,ios::end);
    int fileSize=in.tellg();
    in.seekg(0,ios::beg);*/
    in.seekg(18,ios::beg); 
    in.read((char*) &width, 4);
    in.read((char*) &height, 4);
    in.seekg(0,ios::beg);
    in.read((char*)arr,54);
    out.write((char*)arr,54);
//  fileSize-=54;
    color c;
    color carr1[width+1], carr2[width+1];	
    for(unsigned int i=0;i<height;i+=2)
    {
    	for(unsigned int j=0;j<width;j+=2)
    	{
    		in.read((char*)&c,3);
    		carr1[j] = carr1[j+1] = carr2[j] = carr2[j+1] = (c +4);	
    	}
    	out.write((char*)carr1, width*3);
    	out.write((char*)carr2, width*3);    	
    	out.flush();
    }
    out.close();
}



int main(int argc,char **argv)
{
    if(argc<2)
    {
        cout<<"Argument Missing!\n";
        return 0;
    }
    
    ofstream out1("header",ios::binary);
    ofstream out2("color.pkr",ios::binary);
    ofstream out3("count.pkr",ios::binary);
    ifstream in(argv[1],ios::binary);
    char arr[56];
 
    in.read((char*)arr,54);
    out1.write((char*)arr,54);
    out1.flush();
    int size=0;
    in.read((char*)&size,4);
    
    copy(in,out2,size);
    
    in.read((char*)&size,4);
    
    copy(in,out3,size);   
    
    if (system("./16bitdecomp color.pkr") < 0) {
	cerr << "Unable to execute command :" << "./16bitdecomp color.pkr"
	<< endl;
    }
    if (system("./8bitdecomp count.pkr") < 0) {
	cerr << "Unable to execute command :" << "./8bitdecomp count.pkr"
	<< endl;
    }
    if (system("rm color.pkr count.pkr") < 0) {
	cerr << "Unable to execute command :" << "rm color.pkr count.pkr"
	<< endl;
    }
       
    firstPhaseDecomp();   
    secondPhaseDecomp((char*)"decomp.rle");
    thirdPhaseDecomp((char*)"expand.bmp");
    if (system("rm decomp.rle decompcolor decompcount header expand.bmp") < 0) {
	cerr << "Unable to execute command :" << "rm color.pkr count.pkr"
	<< endl;
    }
}



