#pragma once
#include <memory>
#include <string>
#include "log_format.h"
#include "log_output.h"

// ��־����
enum class LogLevel {
	DEBUG,
	INFO,
	ERROR,
	FATAL
};

// Logger aggregates a formatter and an output sink.
class Logger {
public:
	/////////////////////////
	/// ��ʽ��д����־
	/// @para level ��־����
	/// @para log ��־����
	///	@para file Դ�ļ�·��
	/// @para line �����к�
	/////////////////////////
	void write(LogLevel level, const std::string& log, const std::string& file, int line);

	void setOutput(std::unique_ptr<LogOutput> output) { m_output = std::move(output); }
	void setFormater(std::unique_ptr<LogFormat> formater) { m_formater = std::move(formater); }

	void setLowestLevel(LogLevel level) { m_lowestLevel = level; }

private:
	std::unique_ptr<LogFormat> m_formater;
	std::unique_ptr<LogOutput> m_output;

	// �����־����Ĭ��DEBUG
	LogLevel m_lowestLevel{ LogLevel::DEBUG };
};

