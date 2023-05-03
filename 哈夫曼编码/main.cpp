#include"HuffmanTree.h"



int main()
{
	HuffmanTree hft;
	//hft.InitHFT();
	//unordered_map<char, string > code = hft.CreateHFMcode();
	hft.InitHFTFromFile("test1.txt");
	hft.show();
	system("pause");
	return 0;
}