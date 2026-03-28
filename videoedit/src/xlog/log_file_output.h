#pragma once
#include <fstream>
#include "log_output.h"
class LogFileOutput : public LogOutput {
public:
	/// <summary>
	/// 打开写入日志文件
	/// <param name = "file">文件路径</param>
	/// <returns>打开文件是否成功</returns>
	bool open(const std::string& file);

	////////////////////////////////
	/// 日志输出
	/// @para log 格式化后的日志内容
	////////////////////////////////
	void output(const std::string& log) override;

private:
	std::ofstream ofs;
};
