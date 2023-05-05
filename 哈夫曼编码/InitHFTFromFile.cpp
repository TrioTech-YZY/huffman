#include"HuffmanTree.h"

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