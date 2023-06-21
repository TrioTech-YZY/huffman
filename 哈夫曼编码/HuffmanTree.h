/*
*文件名称：				HuffmanTree.h
*项目名称：				哈夫曼编码
*创建者：				N
*创建时间：				2023.5.2
*最后修改时间：			2023.5.3
*功能：					对未编码文件或编码文件进行读取，通过哈夫曼编码对文件进行编码或译码，并将相应结果保存到文件中；对指定文件数据进行编码，将结果保存并打印。
*文件中的函数：         打印函数、编码函数
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

void Print(); //打印函数,打印CodeFile.bin中的字符，并写入到CodePrint.txt中
void Encode(); //编码函数，根据record.txt中字母对应的编码规则，将ToBeTran.txt中数据编码，写入CodeFile.bin中


//结构体名称：HFT
//定义该结构体的目的：构造哈夫曼树
typedef struct HFT {
	char data;
	int weight;
	int lchild, rchild, parent;
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

class HuffmanTree {
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
	PHFT getStart() {
		return start;
	}
};
//函数名称：哈夫曼编码函数
//功能描述：根据创建的哈夫曼树，构造每个字符的哈夫曼编码
//预备条件：有一颗哈夫曼树
//参数列表：无
//后置条件：以unordered_map<char, string>形式返回字符及其编码的对应关系
unordered_map<char, string> HuffmanTree::CreateHFMcode() {
	unordered_map<char, string> HFCode;
	string temp;
	stack<string> st;		//利用栈实现上一个char类型strcpy的方法
	int cur = 0, father = 0;
	for (int i = 1; i <= start[0].weight; i++) {
		cur = i;
		father = start[i].parent;
		while (father != 0)
		{
			if (start[father].lchild == cur) st.push("0");
			else st.push("1");
			cur = father;
			father = start[father].parent;
		}
		while (!st.empty()) {
			temp += st.top();
			st.pop();
		}
		HFCode[start[i].data] = temp;
		temp.erase();	//擦除内存
	}
	return HFCode;
}

//函数名称：构造函数
//功能描述：将哈夫曼数组起始指针置空
//预备条件：无
//参数列表：无
//后置条件：无
HuffmanTree::HuffmanTree() {
	start = NULL;
}

//函数名称：析构函数
//功能描述：从堆区删除哈夫曼树组
//预备条件：无
//参数列表：无
//后置条件：堆区哈夫曼数组空间释放
HuffmanTree::~HuffmanTree() {
	delete[] start;
}

//函数名称：选择函数
//功能描述：在哈夫曼森林中，选择两个权值最小的树
//预备条件：至少存在两棵树
//参数列表：无
//后置条件：树的编号通过引用方式返回
void HuffmanTree::select(PHFT start, int end, int& min1, int& min2) {
	for (int i = 1; i < end; i++) {
		if (start[i].parent == 0) {
			min1 = i;
			break;
		}
	}
	for (int i = min1 + 1; i < end; i++) {
		if (start[i].weight < start[min1].weight && start[i].parent == 0)
			min1 = i;
	}
	for (int j = 1; j < end; j++) {
		if (start[j].parent == 0 && j != min1) {
			min2 = j;
			break;
		}
	}
	for (int j = min2 + 1; j < end && j != min1; j++) {
		if (start[j].weight < start[min2].weight && start[j].parent == 0)
			min2 = j;
	}
}

//函数名称：终端初始化函数
//功能描述：通过终端输入字符及其权值，创建一颗哈夫曼树
//预备条件：输入结点个数大于2
//参数列表：无
//后置条件：堆区创建一颗哈夫曼树
void HuffmanTree::InitHFT() {
	cout << "请输入字符集个数" << endl;
	int n;
	cin >> n;
	if (n <= 1) {
		cout << "你输入的字符集个数不合法！" << endl;
		return;
	}
	start = new HFT[2 * n];
	start[0].weight = n;
	for (int i = 1; i < 2 * n; i++) {
		start[i].data = '#';
		start[i].weight = 0;
		start[i].lchild = 0;
		start[i].rchild = 0;
		start[i].parent = 0;
	}
	for (int i = 1; i <= n; i++) {
		cout << "请输入字符：" << endl;
		char c;
		cin >> c;
		start[i].data = c;
		cout << "请输入字符权值：" << endl;
		int w;
		cin >> w;
		start[i].weight = w;
	}
	for (int i = n + 1; i < 2 * n; i++) {
		int min1, min2;
		select(start, i, min1, min2);
		start[min1].parent = i;
		start[min2].parent = i;
		start[i].lchild = min1;
		start[i].rchild = min2;
		start[i].weight = start[min1].weight + start[min2].weight;
	}
}



//函数名称：文件读入初始化函数
//功能描述：从文件中读取字符及其权值，构造哈夫曼树
//预备条件：文件不为空
//参数列表：文件路径
//后置条件：堆区创建哈夫曼树
void HuffmanTree::InitHFTFromFile(string filename) {

	std::unordered_map<char, int> cw; //char_weight 从文件中读取的字符和权值保存到cw中

	// 创建一个输入文件流对象
	std::ifstream infile(filename);

	// 检查文件是否打开成功
	if (!infile.is_open()) {
		std::cout << "Error: failed to open file.\n";
		return;
	}

	// 读取文件中的数据，并存储到unordered_map对象中
	std::string line;
	while (std::getline(infile, line)) {
		char key = line[0];
		int value = std::stoi(line.substr(2));
		cw[key] = value;
	}
	int n = cw.size();
	start = new HFT[2 * n];
	start[0].weight = n;
	for (int i = 1; i < 2 * n; i++) {
		start[i].data = '#';
		start[i].weight = 0;
		start[i].lchild = 0;
		start[i].rchild = 0;
		start[i].parent = 0;
	}
	int i = 1;
	for (auto it = cw.begin(); it != cw.end(); ++it) {
		start[i].data = it->first;
		start[i].weight = it->second;
		++i;
	}
	for (int i = n + 1; i < 2 * n; i++) {
		int min1, min2;
		select(start, i, min1, min2);
		start[min1].parent = i;
		start[min2].parent = i;
		start[i].lchild = min1;
		start[i].rchild = min2;
		start[i].weight = start[min1].weight + start[min2].weight;
	}

}

//函数名称：文件读入哈夫曼编码函数
//功能描述：从文件中读取字符及其对应的哈夫曼编码
//预备条件：文件不为空
//参数列表：文件路径
//后置条件：内存中存入字符及其对应编码的映射关系
unordered_map<char, string> HuffmanTree::readCodeFromFile(string filename) {
	std::unordered_map<char, string> code;

	// 创建一个输入文件流对象
	std::ifstream infile(filename);

	// 检查文件是否打开成功
	if (!infile.is_open()) {
		std::cout << "Error: failed to open file.\n";
		return {};
	}

	// 读取文件中的数据，并存储到unordered_map对象中
	std::string line;
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		char key;
		string value;
		//调用两次getline函数是为了去除中间的"|"
		if (ss >> key && std::getline(ss, value, '|') && std::getline(ss, value)) {
			code[key] = value;
		}
	}

	// 关闭文件流
	infile.close();
	return code;


}

//函数名称：文件保存哈夫曼编码函数
//功能描述：将每个字符及其对应的哈夫曼编码保存到文件中
//预备条件：存在哈夫曼编码
//参数列表：字符及其编码的映射集合，文件路径
//后置条件：文件中保存字符及其对应编码
void HuffmanTree::saveCodeToFile(unordered_map<char, string> code, string filename) {

	std::ofstream outfile(filename);

	// 检查文件是否打开成功
	if (!outfile.is_open()) {
		std::cout << "Error: failed to open file.\n";
		return;
	}

	// 将unordered_map数据写入文件
	for (const auto& pair : code) {
		outfile << pair.first << "|" << pair.second << "\n";
	}

	// 关闭文件流
	outfile.close();



}

//函数名称：展示函数
//功能描述：将哈夫曼数组信息在终端展示
//预备条件：哈夫曼数组存在
//参数列表：无
//后置条件：终端打印数组信息
void HuffmanTree::show() {
	int m = 2 * start[0].weight - 1;
	for (int i = 1; i <= m; i++) {
		cout << "第" << i << "结点" << "\t字符为：" << start[i].data
			<< "\tweight为:" << start[i].weight << "\tparent为：" <<
			start[i].parent << "\tlchild为：" << start[i].lchild
			<< "\tlchild为：" << start[i].rchild << endl;
	}
}



//函数名称：打印函数
//函数功能描述：打印CodeFile.bin中的字符，并写入到CodePrint.txt中
//函数调用之前的预备条件：CodeFile.bin中已经存有字符
//参数列表：无
//后置条件：CodePrint.txt中写入数据
void Print() {
	//打开CodeFile.bin二进制文件
	ifstream in("CodeFile.bin", ios::binary);
	if (!in) {//打开失败
		cout << "Cannot open input file.\n";
		abort();
	}
	//打开CodePrint.txt文本文件
	ofstream fout("CodePrint.txt", ios::out);
	if (!fout) {//打开失败
		cout << "Cannot open output file." << endl;
		exit(1);
	}

	char ch;//文件读取的字符放入ch
	int ct = 0;//用于记录读取的字符数

	while (in.read((char*)&ch, sizeof(ch))) {//从CodeFile.bin中每次读取一个字符
		cout << ch;//显示该字符
		if (ch == '1' || ch == '0') {
			ct++;//自加1
			if (ct % 50 == 0) { cout << endl; }//每读取五十个有效字符，换行
		}
		fout << ch;//将字符写入到CodePrint.txt中
	};
	//关闭两文件
	fout.close();
	in.close();

}


//函数名称：编码函数
//函数功能描述：根据record.txt中字母对应的编码规则，将ToBeTran.txt中数据编码，写入CodeFile.bin中
//函数调用之前的预备条件：record.txt中已经保存有字母的编码规则
//参数列表：无
//后置条件：CodeFile.bin二进制文件中写入内容
void Encode() {
	HuffmanTree hf;//实例化一个哈夫曼树对象

	unordered_map<char, string> map;//定义一个哈希表map
	map = hf.readCodeFromFile("test.txt");//调用函数得到字母和二进制串的对应关系，放入map中
	//读ToBeTran.txt文本文件
	ifstream infile;
	infile.open("ToBeTran.txt", ios::in);
	if (!infile) {//打开文件失败
		cout << "Cannot open the file***.\n";
		exit(1);
	}
	//写CodeFile.bin二进制文件
	ofstream outfile;
	outfile.open("CodeFile.bin", ios::out | ios::binary);
	if (!outfile) {//打开文件失败
		cerr << "Cannot open the file.\n";
		exit(1);
	}

	char ch;
	while ((ch = infile.get()) != EOF) {//每次从ToBeTran.txt中读取一个字符放入ch中
		//cout << ch;
		if (ch == ' ') { continue; }//为空格则跳到下次循环
		string str = map[ch];
		char* s = (char*)str.data();//将string类型变为char类型
		outfile.write((char*)s, sizeof(s));//将二进制串写入CodeFile.bin文件中
	}
	//关闭文件
	infile.close();
	outfile.close();
}

void testEncode() {
	ifstream infile("ToBeTran.txt",ios::in);
	if (!infile) {
		cout << "打开文件失败！";

	}
	else {
		cout << "success";
	}
}
