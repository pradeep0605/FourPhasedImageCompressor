#include "secondPhase.cpp"

void thirdPhase(char *s)
{
   
   
   unsigned char arr[56];
   ofstream outs("header",ios::binary);
   ofstream outs2("color",ios::binary);
   ofstream outs3("count",ios::binary);
   
   ifstream ins(s,ios::binary);
   ins.seekg(0,ios::end);
   int temp=ins.tellg();
   ins.seekg(0,ios::beg);
   ins.read((char*)arr,54);
   outs.write((char*)arr,54);
   temp-=54;
   
   unsigned long count=0;
   unsigned char finalcount=0;
   color base,next;
   ins.read((char*)&base,sizeof(color));
   temp-=3;
   next=base;
   unsigned char ch[3];
   unsigned short res=0;

   while(temp>2)
   {
       count=0;
       base=next;
       
      
       do
       {
	 count++;
	 ins.read((char*)&next,sizeof(color));
	 temp-=3;
       }
       while(next.red==base.red && next.blue==base.blue && next.green==base.green && temp>2);
       while(count>=255)
       {
           res=0;
           /*wite base color with 16 bit representation*/
	       ch[0]=base.red;
	       ch[1]=base.green;
	       ch[2]=base.blue;
	       for(int i=0;i<3;i++)
	       {
		      res=res*32;
		      res=res+(unsigned short) ch[i];
		      
	       }   
	       outs2.write((char*)&res,sizeof(unsigned short)); 
          //base Written
	  finalcount=255;
	  outs3.write((char*)&finalcount,sizeof(unsigned char));
	  count-=255;
	  
	  
	  
	  
       }

	  finalcount=(unsigned char)count;
         res=0;
           /*wite base color with 16 bit representation*/
	       ch[0]=base.red;
	       ch[1]=base.green;
	       ch[2]=base.blue;
	       for(int i=0;i<3;i++)
	       {
		      res=res*32;                                           //  conversion from
		      res=res+(unsigned short) ch[i];                       //  24 bit to 16
		      
	       }   
	       outs2.write((char*)&res,sizeof(unsigned short)); 
          //base Written
	       outs3.write((char*)&finalcount,sizeof(unsigned char));

   }
   outs.flush();
   outs2.flush();
   outs3.flush();
   outs.close();
   outs2.close();
   outs3.close();
   
   system("./16bitcomp color");
   system("./8bitcomp count");
   system("rm color count");
   
}
