#include"HuffmanTree.h"

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
