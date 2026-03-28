#pragma once
#include <string>

///////////////////////////
/// LogFormat日志格式化接口
///////////////////////////
class LogFormat {
public:
	virtual ~LogFormat() = default;
	virtual std::string format(
		const std::string& level,
		const std::string& log,
		const std::string& file,
		int line) = 0;
};

