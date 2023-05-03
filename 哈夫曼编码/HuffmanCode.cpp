#include"HuffmanTree.h"

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
			if (start[father].LChild == cur) st.push("0");
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