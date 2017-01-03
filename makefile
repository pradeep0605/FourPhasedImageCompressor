all:
	g++ comp.cpp -o comp
	g++ decomp.cpp -o decomp
	g++ Huffman/8bit/comp.cpp -o 8bitcomp
	g++ Huffman/8bit/decomp.cpp -o 8bitdecomp
	g++ Huffman/16bit/comp.cpp -o 16bitcomp
	g++ Huffman/16bit/decomp.cpp -o 16bitdecomp

clean:
	rm comp decomp 8bitcomp 8bitdecomp 16bitcomp 16bitdecomp
