#include <algorithm>
#include <cctype>
#include <iostream>
#include "log_factory.h"
#include "log_console_output.h"
#include "log_file_output.h"
#include "xconfig.h"
#include "xlog_format.h"

#define LOGFILE "log.txt"

using namespace std;

static string ToLowerCopy(string s) {
	transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
	return s;
}

void LogFactory::init(const std::string& confile) {
	XConfig config;
	auto re = config.read(confile);
	string log_type = "console"; // default output type
	string log_file = LOGFILE;   // default file path
	string log_level = "debug";  // default minimum level

	if (re) {
		log_type = config.get("log_type");
		log_file = config.get("log_file");
		log_level = config.get("log_level");
	}

	m_logger.setFormater(new XLogFormat());

	log_level = ToLowerCopy(log_level);
	log_type = ToLowerCopy(log_type);

	if (log_level == "info") {
		m_logger.setLowestLevel(LogLevel::INFO);
	}
	else if (log_level == "error") {
		m_logger.setLowestLevel(LogLevel::ERROR);
	}
	else if (log_level == "fatal") {
		m_logger.setLowestLevel(LogLevel::FATAL);
	}
	else {
		m_logger.setLowestLevel(LogLevel::DEBUG);
	}

	if (log_type == "file") {
		if (log_file.empty()) {
			log_file = LOGFILE;
		}
		auto fout = new LogFileOutput();
		if (!fout->open(log_file)) {
			cerr << "open file failed " << log_file << endl;
			delete fout;
			m_logger.setOutput(new LogConsoleOutput);
			return;
		}
		m_logger.setOutput(fout);
	}
	else {
		m_logger.setOutput(new LogConsoleOutput);
	}
}

