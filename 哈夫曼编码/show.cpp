#include"HuffmanTree.h"


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
			start[i].parent << "\tLChild为：" << start[i].LChild
			<< "\tLChild为：" << start[i].RChild << endl;
	}
}