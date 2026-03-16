#include "log_file_output.h"

using namespace std;

bool LogFileOutput::open(const std::string& file) {
	ofs.open(file, ios::app);
	if(!ofs.is_open()){
		return false;
	}
	return true;
}

void LogFileOutput::output(const std::string& log) {
	ofs << log << "\n";
}