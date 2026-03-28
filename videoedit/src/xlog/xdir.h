#pragma once
#include <string>
#include <vector>
#include "xlog.h"

/// <summary>
/// 目录处理，默认C++17
/// </summary>

struct XLOG_API XFile {
	std::string filename;
	std::string path;
	std::string extension;
};

class XLOG_API XDir {
public:
	/// <summary>
	/// 获取path目录下的所有文件
	/// </summary>
	/// <param name="path">目标路径</param>
	/// <returns>目标路径文件列表</returns>
	std::vector<XFile> getFiles(const std::string& path);

	static bool isDir(const std::string& path);
	static bool createDir(const std::string& path);
};

