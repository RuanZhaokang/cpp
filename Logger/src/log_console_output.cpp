#include <iostream>
#include "log_console_output.h"

using namespace std;

void LogConsoleOutput::output(const std::string& log) {
	cout << log << '\n';
}
