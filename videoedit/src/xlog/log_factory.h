#pragma once
#include <string>
#include "logger.h"
#include "xlog.h"

//////////////////////////////////
/// Logger工厂类
/// 维护Logger生命周期，构建Logger
//////////////////////////////////
class XLOG_API LogFactory {
public:
	static LogFactory& instance() {
		static LogFactory factory;
		return factory;
	}

	// 初始化Logger对象
	void init(const std::string& confile = "log.conf");

	Logger& logger() { return m_logger; }

private:
	LogFactory() = default;
	Logger m_logger;
};

#define LOGINIT() do { LogFactory::instance().init(); } while (0)
#define LOGDEBUG(s) do { LogFactory::instance().logger().write(LogLevel::DEBUG, (s), __FILE__, __LINE__); } while (0)
#define LOGINFO(s)  do { LogFactory::instance().logger().write(LogLevel::INFO,  (s), __FILE__, __LINE__); } while (0)
#define LOGERROR(s) do { LogFactory::instance().logger().write(LogLevel::ERROR, (s), __FILE__, __LINE__); } while (0)
#define LOGFATAL(s) do { LogFactory::instance().logger().write(LogLevel::FATAL, (s), __FILE__, __LINE__); } while (0)

