#include"HuffmanTree.h"

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
        return ;
    }

    // 将unordered_map数据写入文件
    for (const auto& pair : code) {
        outfile << pair.first << "|" << pair.second << "\n";
    }

    // 关闭文件流
    outfile.close();



}