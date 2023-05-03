/*
*文件名称：				HuffmanTree.h
*项目名称：				哈夫曼编码
*创建者：				张宇
*创建时间：				2023.5.2
*最后修改时间：			2023.5.3
*功能：					对未编码文件或编码文件进行读取，通过哈夫曼编码对文件进行编码或译码，并将相应结果保存到文件中
*文件中的类与结构体：	结点结构体和哈夫曼树组
*与其他文件的依赖关系：	类中函数声明在对应函数名cpp中，具体使用在main.cpp
*/

#pragma once
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include<stack>
#include<unordered_map>
using namespace std;

//结构体名称：HFT
//定义该结构体的目的：构造哈夫曼树
typedef struct HFT{
	char data;
	int weight;
	int LChild, RChild, parent;
}HFT, * PHFT;

//类名称：		  HuffmanTree
//定义该类的目的：进行哈夫曼树的相关操作
//类属性：		  哈夫曼数组起始地址指针start
//类中函数及功能：
//1.构造函数与析构函数：构造函数初始化start指针为空，析构函数释放哈夫曼树组
//2.InitHFT()：终端初始化字段及其权值，创建哈夫曼树
//3.InitHFTFromFile()：文件中读入字符及其权值，创建哈夫曼树
//4.CreateHFMcode()：构造每个字符的哈夫曼编码，将字符和编码的对应关系以unordered_map形式返回
//5.saveCodeToFile()：将每个字符及其编码保存到文件中
//6.readCodeFromFile()：从文件中读取字符及其哈夫曼编码，保存到内存的unordered_map中
//7.show()：展示哈夫曼数组

class HuffmanTree{
private:
	PHFT  start;
	void select(PHFT start, int end, int& max1, int& max2);
public:
	HuffmanTree();
	~HuffmanTree();
	void InitHFT();     
	void InitHFTFromFile(string filename);   
	unordered_map<char, string> CreateHFMcode(); 
	void saveCodeToFile(unordered_map<char, string> code, string filename);  
	unordered_map<char, string> readCodeFromFile(string filename);   
	void show();
	//需要访问哈夫曼树的静态链表，所以需要一个get方法
	PHFT get_start() {
		return start;
	}
};





