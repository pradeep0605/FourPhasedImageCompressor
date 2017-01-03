#include<iostream>
#include "color.cpp"
#include<fstream>

using namespace std;

void ff()
{
	char h[54];
	ifstream in("images/elephant.bmp", ios::binary);
	ofstream out("images/temp.bmp", ios::binary);
	in.seekg(0, ios::end);
	int filesize = in.tellg();
	in.seekg(0, ios::beg);
	in.read((char *)h, 54);
	out.write((char *)h, 54);
	filesize-=54;
	
	color b, n;
	in.read((char *)&b, sizeof(color));
	out.write((char *)&b, sizeof(color));
	filesize-=3;
	
	while(filesize>2)
	{
	  in.read((char *)&n, sizeof(color));
	  filesize-=3;
	  
	  if(b==n)
	  {
	    out.write((char *)&b, sizeof(color));
	  }
	  else
	  {
	   out.write((char *)&n, sizeof(color));
	   b=n;
	  }
	}
	in.read((char *)h, filesize);
	out.write((char *)h, filesize);
	in.close();
	out.close();
}

int main()
{
	ff();	
	return 0;
}
