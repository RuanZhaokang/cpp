#pragma once
#include "log_output.h"

class LogConsoleOutput : public LogOutput {
public:
	////////////////////////////////
	/// 日志输出
	/// @para log 格式化后的日志内容
	////////////////////////////////
	void output(const std::string& log) override;
};
