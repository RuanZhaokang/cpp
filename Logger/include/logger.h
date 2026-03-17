#pragma once
#include <memory>
#include <string>
#include "log_format.h"
#include "log_output.h"

// 日志级别
enum class LogLevel {
	DEBUG,
	INFO,
	ERROR,
	FATAL
};

//////////////////
/// 聚合类
/// 委托 LogFormat
///      LogOutput
//////////////////
class Logger {
public:
	/////////////////////////
	/// 格式化写入日志
	/// @para level 日志级别
	/// @para log 日志内容
	///	@para file 源文件路径
	/// @para line 代码行号
	/////////////////////////
	void write(LogLevel level, const std::string& log, const std::string& file, int line);

	void setOutput(std::unique_ptr<LogOutput> output) { m_output = std::move(output); }
	void setFormater(std::unique_ptr<LogFormat> formater) { m_formater = std::move(formater); }

	void setLowestLevel(LogLevel level) { m_lowestLevel = level; }

private:
	std::unique_ptr<LogFormat> m_formater;
	std::unique_ptr<LogOutput> m_output;

	// 最低默认级别，默认DEBUG
	LogLevel m_lowestLevel{ LogLevel::DEBUG };
};

