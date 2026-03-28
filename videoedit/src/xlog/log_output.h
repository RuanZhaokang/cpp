#pragma once
#include <string>

////////////////////////////
/// 日志输出接口，输出到设备
///////////////////////////
class LogOutput {
public:
	virtual ~LogOutput() = default;

	////////////////////////////////
	/// 日志输出
	/// @para log 格式化后的日志内容
	/// @para file 源码文件路径
	/// @para line 代码行号
	/// @return 格式化后的日志
	///////////////////////////////
	virtual void output(const std::string& log) = 0;
};

