#include"HuffmanTree.h"

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




