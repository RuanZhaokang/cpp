#pragma once
#include "log_format.h"
class XLogFormat : public LogFormat {
public:
	/////////////////////////////////////
	/// 格式化返回字符串
	/// @para level 日志级别
	/// @para log 日志内容
	/// @para file 源文件路径
	/// @para line 代码行号
	/// @para return 返回格式化后的字符串
	////////////////////////////////////
	std::string format(const std::string& level, const std::string& log, const std::string& file, int line) override;
};
