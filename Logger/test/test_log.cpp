#include <iostream>
#include "log_factory.h"
#include "logger.h"
#include "xconfig.h"
//#include "xlog_format.h"
//#include "log_console_output.h"
//#include "log_file_output.h"
//#include "logger.h"

using namespace std;

int main() {
	LogFactory::instance().init("log.conf");
	LOGDEBUG("test log debug");
	LOGINFO("test log info");
	LOGERROR("test log error");
	LOGFATAL("test log fatal");

	return 0;
}