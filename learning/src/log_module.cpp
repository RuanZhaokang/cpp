#include <iostream>

using namespace std;

enum class LogLevel 
{
	DEBUG,
	INFO,
	ERROR,
	FATAL
};

int main(int argc,char *argv[]) {
	// 用户传递日志的最低显示日志级别
	// DEBUG < INFO < ERROR < FATAL
	auto loglevel = LogLevel::DEBUG; // 默认最低日志级别DEBUG
	if (argc > 1) {
		string levelstr = argv[1];
		if ("INFO" == levelstr)
			loglevel = LogLevel::INFO;
		else if ("ERROR" == levelstr)
			loglevel = LogLevel::ERROR;
		else if("FATAL" == levelstr)
			loglevel = LogLevel::FATAL;
	}

	// 测试DEBUG
	{
		auto level = LogLevel::DEBUG;
		string context = "test log 1";
		if (level >= loglevel) {
			string levelstr = "DEBUG";
			switch (level)
			{
			case LogLevel::INFO: 
				levelstr = "INFO"; break;
			case LogLevel::ERROR: 
				levelstr = "ERROR"; break;
			case LogLevel::FATAL: 
				levelstr = "FATAL"; break;
			}

			cout << "[" << levelstr << "]" << ":" << context << endl;
		}
	}

	// 测试INFO
	{
		auto level = LogLevel::INFO;
		string context = "test log 2";
		if (level >= loglevel) {
			string levelstr = "DEBUG";
			switch (level)
			{
			case LogLevel::INFO:
				levelstr = "INFO"; break;
			case LogLevel::ERROR:
				levelstr = "ERROR"; break;
			case LogLevel::FATAL:
				levelstr = "FATAL"; break;
			}

			cout << "[" << levelstr << "]" << ":" << context << endl;
		}
	}

	// 测试ERROR
	{
		auto level = LogLevel::ERROR;
		string context = "test log 3";
		if (level >= loglevel) {
			string levelstr = "DEBUG";
			switch (level)
			{
			case LogLevel::INFO:
				levelstr = "INFO"; break;
			case LogLevel::ERROR:
				levelstr = "ERROR"; break;
			case LogLevel::FATAL:
				levelstr = "FATAL"; break;
			}

			cout << "[" << levelstr << "]" << ":" << context << endl;
		}
	}

	// 测试FATAL
	{
		auto level = LogLevel::FATAL;
		string context = "test log 4";
		if (level >= loglevel) {
			string levelstr = "DEBUG";
			switch (level)
			{
			case LogLevel::INFO:
				levelstr = "INFO"; break;
			case LogLevel::ERROR:
				levelstr = "ERROR"; break;
			case LogLevel::FATAL:
				levelstr = "FATAL"; break;
			}

			cout << "[" << levelstr << "]" << ":" << context << endl;
		}
	}

	return 0;
}