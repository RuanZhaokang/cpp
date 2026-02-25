#pragma once
#include <iostream>
#include <vector>
#include <string>

///////////////////////////////////////////////
//// Base16编码
///@para data 需要编码的二进制数据
///@return 编码后的Base16字符串，失败时返回空串
std::string Base16Encode(const std::vector<unsigned char>& data);

///////////////////////////////////////////////
//// Base16解码
///@para data Base16的解码字符串
///@return 解码后的二进制数据
std::vector<unsigned char> Base16Decode(const std::string & data);