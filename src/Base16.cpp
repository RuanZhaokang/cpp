#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string str;
    cout << "请输入一个字符串：" << endl;
    cin >> str;
    cout << "str = " << "\"" << str << "\"" << endl;

    // Base16编码：使用16进制字符表示二进制
    string encode_tab = "0123456789ABCDEF"; // 16进制映射表
    string Base16str;
    for (unsigned char ch : str) {
        char hBit = ch >> 4; // 获取字符串单个字符高位
        char lBit = ch & 0b00001111; // 获取字符串单个字符低位

        Base16str += encode_tab[hBit];
        Base16str += encode_tab[lBit];
    }

    cout << "编码结果：" << Base16str << endl;

    // Base16解码：将编码后的Base16字符串重新解码还原
    string ostr; // 原字符串
    vector<char> decode_tab = { // ASCII字符映射表
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 0~9
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 10~19
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 20~29
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 30~39
        -1,-1,-1,-1,-1,-1,-1,-1, 0, 1, // 40~49
         2, 3, 4, 5, 6, 7, 8, 9, -1,-1, // 50~59
         -1,-1,-1,-1,-1,10,11,12,13,14, // 60~69
         15 // 70
    };
    for (int i = 0; i < Base16str.size(); i += 2) { // 两位表示一个字符
        char hc = Base16str[i]; // 获取Base16编码后的高位字符
        char lc = Base16str[i + 1]; // 获取Base16编码后的低位字符

        unsigned char h = decode_tab[hc]; // 通过映射表获取解码高位（0-15）
        unsigned char l = decode_tab[lc]; // 通过映射表获取解码低位（0-15）

        ostr += (h << 4 | l); // 合并高位低位字符为一个解码字符
    }
    cout << "解码结果：" << ostr << endl;

    return 0;
}
