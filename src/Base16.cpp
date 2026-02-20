#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// 读取文件数据，转换为字符存储
vector<unsigned char> read_file(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cout << "文件打开失败！" << endl;
        return {};
    }

    return vector<unsigned char>(
        istreambuf_iterator<char>(ifs),
        istreambuf_iterator<char>()
    );
}

// Base16编码
string base16_encode(const vector<unsigned char>& data) {
    static const string tab = "0123456789ABCDEF";
    string output;
    output.reserve(data.size() * 2);

    for (unsigned char ch : data) {
        output += tab[ch >> 4]; // 获取高位
        output += tab[ch & 0b00001111]; // 获取低位
    }   

    return output;
}

// 将Base16编码结果写入文本文件
void write_text(const string& filename, const string& text) {
    ofstream ofs(filename);
    if (!ofs) {
        cout << "文本文件写入失败！" << endl;
        return;
    }
    ofs << text;
}

// 从文本文件读取Base16字符串
string read_text(const string& filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cout << "文本文件读取失败！" << endl;
        return {};
    }

    string content, line;
    while (getline(ifs, line)) {
        content += line;
    }
    return content;
}

// Base16解码
vector<unsigned char> base16_decode(const string& hex) {
    vector<unsigned char> output;
    output.reserve(hex.size() / 2);
    
    auto val = [](char c) -> int {
        if ('0' <= c && c <= '9') return c - '0';
        if ('A' <= c && c <= 'F') return c - 'A' + 10;
        return -1;
    };

    for (int i = 0; i < hex.size(); i += 2) {
        int h = val(hex[i]);
        int l = val(hex[i + 1]);
        output.push_back((h << 4 | l));
    }
    return output;
}

// 解码Base16字符串后生成解码文件
void write_file(const string& filename, const vector<unsigned char>& data) {
    ofstream ofs(filename, ios::binary);
    ofs.write((const char*)data.data(), data.size());
}

int main()
{
    //string str;
    //cout << "请输入一个字符串：" << endl;
    //cin >> str;
    //cout << "str = " << "\"" << str << "\"" << endl;

    //// Base16编码：使用16进制字符表示二进制
    //string encode_tab = "0123456789ABCDEF"; // 16进制映射表
    //string Base16str;
    //for (unsigned char ch : str) {
    //    char hBit = ch >> 4; // 获取字符串单个字符高位
    //    char lBit = ch & 0b00001111; // 获取字符串单个字符低位

    //    Base16str += encode_tab[hBit];
    //    Base16str += encode_tab[lBit];
    //}

    //cout << "编码结果：" << Base16str << endl;

    //// Base16解码：将编码后的Base16字符串重新解码还原
    //string ostr; // 原字符串
    //vector<char> decode_tab = { // ASCII字符映射表
    //    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 0~9
    //    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 10~19
    //    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 20~29
    //    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 30~39
    //    -1,-1,-1,-1,-1,-1,-1,-1, 0, 1, // 40~49
    //     2, 3, 4, 5, 6, 7, 8, 9, -1,-1, // 50~59
    //     -1,-1,-1,-1,-1,10,11,12,13,14, // 60~69
    //     15 // 70
    //};
    //for (int i = 0; i < Base16str.size(); i += 2) { // 两位表示一个字符
    //    char hc = Base16str[i]; // 获取Base16编码后的高位字符
    //    char lc = Base16str[i + 1]; // 获取Base16编码后的低位字符

    //    unsigned char h = decode_tab[hc]; // 通过映射表获取解码高位（0-15）
    //    unsigned char l = decode_tab[lc]; // 通过映射表获取解码低位（0-15）

    //    ostr += (h << 4 | l); // 合并高位低位字符为一个解码字符
    //}
    //cout << "解码结果：" << ostr << endl;

    auto data = read_file("C:\\Users\\XiuHong Ruan\\Pictures\\Cyberpunk 2077\\test.png");
    cout << "--------------------测试Base16编码--------------------" << endl;
    auto hex = base16_encode(data);
    cout << "编码结果（前100字符）：" << endl;
    cout << hex.substr(0, 100) << "..." << endl;

    write_text("C:\\Users\\XiuHong Ruan\\Desktop\\image.hex", hex);

    cout << "--------------------测试Base16解码--------------------" << endl;
    auto hexstr = read_text("C:\\Users\\XiuHong Ruan\\Desktop\\image.hex");
    auto decoded = base16_decode(hexstr);
    write_file("C:\\Users\\XiuHong Ruan\\Desktop\\测试用图片.png", decoded);

    return 0;
}