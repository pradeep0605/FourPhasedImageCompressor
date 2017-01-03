#include<iostream>


#include "fourthPhase.cpp"

int main(int argc,char **argv)
{
   if(argc<2)
   {
       cout<<"Arguments missings!";
       return 0;
   }
   char original[100];
   strcpy(original,argv[1]);
   firstPhase(argv[1]);
   cout<<"First  phase done.....\n";
   secondPhase((char *)"firstPhase.bmp");
   cout<<"Second phase done.....\n";
   thirdPhase((char*)"secondPhase.bmp");
   cout<<"Third  phase done.....\n"; 
   fourthPhase(argv[1]);
   cout<<"Fourth phase done.....\n"; 
   if (system("rm firstPhase.bmp") < 0) {
	cerr << "Unable to run the command: rm firstPhase.bmp\n";
   }
   if (system("rm secondPhase.bmp") < 0) {
	cerr << "Unable to run the comamnd: rm secondPhase.bmp\n";
   }
   ifstream in1(original,ios::binary);
   ifstream in2(strcat(original,".pkr"),ios::binary);
    int size1=0,size2=0;
   in1.seekg(0,ios::end);
   in2.seekg(0,ios::end);
   size1=in1.tellg();
   size2=in2.tellg();
   cout<<"\n===============================\n";
   cout<<"      Original\t     Compressed\n";\
   cout<<"===============================\n";
   cout.width(12);	
   cout.precision(6);
   cout<<size1<<" B\t";cout.width(12);cout<<size2<<" B"<<endl;
   cout<<"-------------------------------\n";cout.width(12);
   cout<<float(size1)/1024<<" KB\t"; cout.width(12);cout<<float(size2)/1024<<" KB\n";
   cout<<"-------------------------------\n";cout.width(12);
   cout<<float(size1)/(1024*1024)<<" MB\t"; cout.width(12);cout<<float(size2)/(1024*1024)<<" MB\n";
   cout<<"-------------------------------\n"; 
   cout<<"Compression percentage= "<< ((float(size2)/size1)*-100)+100<<" %"<<endl;
     
    return 0; 
}
