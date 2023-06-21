#include"HuffmanTree.h"
#include"Conventer.h"


int main()
{
	HuffmanTree hft;
	hft.InitHFTFromFile("test1.txt");
	hft.show();
	testEncode();
	Encode();
	Print();
	Converter c(hft.getStart());
	c.setCode("CodeFile.bin");
	system("pause");
	return 0;
}