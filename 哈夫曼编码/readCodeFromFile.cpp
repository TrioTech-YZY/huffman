#include"HuffmanTree.h"

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