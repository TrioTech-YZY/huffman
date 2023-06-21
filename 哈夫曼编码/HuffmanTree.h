/*
*�ļ����ƣ�				HuffmanTree.h
*��Ŀ���ƣ�				����������
*�����ߣ�				N
*����ʱ�䣺				2023.5.2
*����޸�ʱ�䣺			2023.5.3
*���ܣ�					��δ�����ļ�������ļ����ж�ȡ��ͨ��������������ļ����б�������룬������Ӧ������浽�ļ��У���ָ���ļ����ݽ��б��룬��������沢��ӡ��
*�ļ��еĺ�����         ��ӡ���������뺯��
*�ļ��е�����ṹ�壺	���ṹ��͹���������
*�������ļ���������ϵ��	���к��������ڶ�Ӧ������cpp�У�����ʹ����main.cpp
*/

#pragma once
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include<stack>
#include<unordered_map>
using namespace std;

void Print(); //��ӡ����,��ӡCodeFile.bin�е��ַ�����д�뵽CodePrint.txt��
void Encode(); //���뺯��������record.txt����ĸ��Ӧ�ı�����򣬽�ToBeTran.txt�����ݱ��룬д��CodeFile.bin��


//�ṹ�����ƣ�HFT
//����ýṹ���Ŀ�ģ������������
typedef struct HFT {
	char data;
	int weight;
	int lchild, rchild, parent;
}HFT, * PHFT;

//�����ƣ�		  HuffmanTree
//��������Ŀ�ģ����й�����������ز���
//�����ԣ�		  ������������ʼ��ַָ��start
//���к��������ܣ�
//1.���캯�����������������캯����ʼ��startָ��Ϊ�գ����������ͷŹ���������
//2.InitHFT()���ն˳�ʼ���ֶμ���Ȩֵ��������������
//3.InitHFTFromFile()���ļ��ж����ַ�����Ȩֵ��������������
//4.CreateHFMcode()������ÿ���ַ��Ĺ��������룬���ַ��ͱ���Ķ�Ӧ��ϵ��unordered_map��ʽ����
//5.saveCodeToFile()����ÿ���ַ�������뱣�浽�ļ���
//6.readCodeFromFile()�����ļ��ж�ȡ�ַ�������������룬���浽�ڴ��unordered_map��
//7.show()��չʾ����������

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
//�������ƣ����������뺯��
//�������������ݴ����Ĺ�������������ÿ���ַ��Ĺ���������
//Ԥ����������һ�Ź�������
//�����б���
//������������unordered_map<char, string>��ʽ�����ַ��������Ķ�Ӧ��ϵ
unordered_map<char, string> HuffmanTree::CreateHFMcode() {
	unordered_map<char, string> HFCode;
	string temp;
	stack<string> st;		//����ջʵ����һ��char����strcpy�ķ���
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
		temp.erase();	//�����ڴ�
	}
	return HFCode;
}

//�������ƣ����캯��
//������������������������ʼָ���ÿ�
//Ԥ����������
//�����б���
//������������
HuffmanTree::HuffmanTree() {
	start = NULL;
}

//�������ƣ���������
//�����������Ӷ���ɾ������������
//Ԥ����������
//�����б���
//������������������������ռ��ͷ�
HuffmanTree::~HuffmanTree() {
	delete[] start;
}

//�������ƣ�ѡ����
//�����������ڹ�����ɭ���У�ѡ������Ȩֵ��С����
//Ԥ�����������ٴ���������
//�����б���
//�������������ı��ͨ�����÷�ʽ����
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

//�������ƣ��ն˳�ʼ������
//����������ͨ���ն������ַ�����Ȩֵ������һ�Ź�������
//Ԥ���������������������2
//�����б���
//������������������һ�Ź�������
void HuffmanTree::InitHFT() {
	cout << "�������ַ�������" << endl;
	int n;
	cin >> n;
	if (n <= 1) {
		cout << "��������ַ����������Ϸ���" << endl;
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
		cout << "�������ַ���" << endl;
		char c;
		cin >> c;
		start[i].data = c;
		cout << "�������ַ�Ȩֵ��" << endl;
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



//�������ƣ��ļ������ʼ������
//�������������ļ��ж�ȡ�ַ�����Ȩֵ�������������
//Ԥ���������ļ���Ϊ��
//�����б��ļ�·��
//��������������������������
void HuffmanTree::InitHFTFromFile(string filename) {

	std::unordered_map<char, int> cw; //char_weight ���ļ��ж�ȡ���ַ���Ȩֵ���浽cw��

	// ����һ�������ļ�������
	std::ifstream infile(filename);

	// ����ļ��Ƿ�򿪳ɹ�
	if (!infile.is_open()) {
		std::cout << "Error: failed to open file.\n";
		return;
	}

	// ��ȡ�ļ��е����ݣ����洢��unordered_map������
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

//�������ƣ��ļ�������������뺯��
//�������������ļ��ж�ȡ�ַ������Ӧ�Ĺ���������
//Ԥ���������ļ���Ϊ��
//�����б��ļ�·��
//�����������ڴ��д����ַ������Ӧ�����ӳ���ϵ
unordered_map<char, string> HuffmanTree::readCodeFromFile(string filename) {
	std::unordered_map<char, string> code;

	// ����һ�������ļ�������
	std::ifstream infile(filename);

	// ����ļ��Ƿ�򿪳ɹ�
	if (!infile.is_open()) {
		std::cout << "Error: failed to open file.\n";
		return {};
	}

	// ��ȡ�ļ��е����ݣ����洢��unordered_map������
	std::string line;
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		char key;
		string value;
		//��������getline������Ϊ��ȥ���м��"|"
		if (ss >> key && std::getline(ss, value, '|') && std::getline(ss, value)) {
			code[key] = value;
		}
	}

	// �ر��ļ���
	infile.close();
	return code;


}

//�������ƣ��ļ�������������뺯��
//������������ÿ���ַ������Ӧ�Ĺ��������뱣�浽�ļ���
//Ԥ�����������ڹ���������
//�����б��ַ���������ӳ�伯�ϣ��ļ�·��
//�����������ļ��б����ַ������Ӧ����
void HuffmanTree::saveCodeToFile(unordered_map<char, string> code, string filename) {

	std::ofstream outfile(filename);

	// ����ļ��Ƿ�򿪳ɹ�
	if (!outfile.is_open()) {
		std::cout << "Error: failed to open file.\n";
		return;
	}

	// ��unordered_map����д���ļ�
	for (const auto& pair : code) {
		outfile << pair.first << "|" << pair.second << "\n";
	}

	// �ر��ļ���
	outfile.close();



}

//�������ƣ�չʾ����
//������������������������Ϣ���ն�չʾ
//Ԥ���������������������
//�����б���
//�����������ն˴�ӡ������Ϣ
void HuffmanTree::show() {
	int m = 2 * start[0].weight - 1;
	for (int i = 1; i <= m; i++) {
		cout << "��" << i << "���" << "\t�ַ�Ϊ��" << start[i].data
			<< "\tweightΪ:" << start[i].weight << "\tparentΪ��" <<
			start[i].parent << "\tlchildΪ��" << start[i].lchild
			<< "\tlchildΪ��" << start[i].rchild << endl;
	}
}



//�������ƣ���ӡ����
//����������������ӡCodeFile.bin�е��ַ�����д�뵽CodePrint.txt��
//��������֮ǰ��Ԥ��������CodeFile.bin���Ѿ������ַ�
//�����б���
//����������CodePrint.txt��д������
void Print() {
	//��CodeFile.bin�������ļ�
	ifstream in("CodeFile.bin", ios::binary);
	if (!in) {//��ʧ��
		cout << "Cannot open input file.\n";
		abort();
	}
	//��CodePrint.txt�ı��ļ�
	ofstream fout("CodePrint.txt", ios::out);
	if (!fout) {//��ʧ��
		cout << "Cannot open output file." << endl;
		exit(1);
	}

	char ch;//�ļ���ȡ���ַ�����ch
	int ct = 0;//���ڼ�¼��ȡ���ַ���

	while (in.read((char*)&ch, sizeof(ch))) {//��CodeFile.bin��ÿ�ζ�ȡһ���ַ�
		cout << ch;//��ʾ���ַ�
		if (ch == '1' || ch == '0') {
			ct++;//�Լ�1
			if (ct % 50 == 0) { cout << endl; }//ÿ��ȡ��ʮ����Ч�ַ�������
		}
		fout << ch;//���ַ�д�뵽CodePrint.txt��
	};
	//�ر����ļ�
	fout.close();
	in.close();

}


//�������ƣ����뺯��
//������������������record.txt����ĸ��Ӧ�ı�����򣬽�ToBeTran.txt�����ݱ��룬д��CodeFile.bin��
//��������֮ǰ��Ԥ��������record.txt���Ѿ���������ĸ�ı������
//�����б���
//����������CodeFile.bin�������ļ���д������
void Encode() {
	HuffmanTree hf;//ʵ����һ��������������

	unordered_map<char, string> map;//����һ����ϣ��map
	map = hf.readCodeFromFile("test.txt");//���ú����õ���ĸ�Ͷ����ƴ��Ķ�Ӧ��ϵ������map��
	//��ToBeTran.txt�ı��ļ�
	ifstream infile;
	infile.open("ToBeTran.txt", ios::in);
	if (!infile) {//���ļ�ʧ��
		cout << "Cannot open the file***.\n";
		exit(1);
	}
	//дCodeFile.bin�������ļ�
	ofstream outfile;
	outfile.open("CodeFile.bin", ios::out | ios::binary);
	if (!outfile) {//���ļ�ʧ��
		cerr << "Cannot open the file.\n";
		exit(1);
	}

	char ch;
	while ((ch = infile.get()) != EOF) {//ÿ�δ�ToBeTran.txt�ж�ȡһ���ַ�����ch��
		//cout << ch;
		if (ch == ' ') { continue; }//Ϊ�ո��������´�ѭ��
		string str = map[ch];
		char* s = (char*)str.data();//��string���ͱ�Ϊchar����
		outfile.write((char*)s, sizeof(s));//�������ƴ�д��CodeFile.bin�ļ���
	}
	//�ر��ļ�
	infile.close();
	outfile.close();
}

void testEncode() {
	ifstream infile("ToBeTran.txt",ios::in);
	if (!infile) {
		cout << "���ļ�ʧ�ܣ�";

	}
	else {
		cout << "success";
	}
}
