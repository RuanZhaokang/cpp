#include "logger.h"

void Logger::write(LogLevel level, const std::string& log, const std::string& file, int line) {
	if (level < m_lowestLevel) return;
	if (!m_formater || !m_output) return;
	
	std::string levelstr = "DEBUG";
	switch (level) {
	case LogLevel::INFO:
		levelstr = "INFO";
		break;
	case LogLevel::ERROR:
		levelstr = "ERROR";
		break;
	case LogLevel::FATAL:
		levelstr = "FATAL";
		break;
	default:
		break;
	}

	// 格式化日志字符串
	auto fmtstr = m_formater->format(levelstr, log, file, line);
	m_output->output(fmtstr);
}
