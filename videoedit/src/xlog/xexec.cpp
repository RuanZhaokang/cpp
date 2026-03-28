#include <iostream>
#include "xexec.h"
#include "log_factory.h"

#ifdef _WIN32
#else
#define _popen popen
#define _pclose pclose
#endif

using namespace std;

bool XExec::start(const char* cmd, function<void(const string&)> func)
{
	/*cout << "start cmd: " << cmd << endl;*/
	LOGINFO("XExec start");

	if (!cmd || *cmd == '\0') {
		LOGERROR("XExec start: empty command!");
		return false;
	}
	// 重定向错误输出到标准输出
	string tmp = (string)cmd + " 2>&1";
	auto fp = _popen(tmp.c_str(), "r"); // 获取标准输出
	if (!fp) {
		LOGERROR("XExec start: popen failed!");
		return false;
	}

	is_running = true;
	m_future = async([fp, this, func]{
		string tmp;
		char ch = 0;
		while ((ch = fgetc(fp)) != EOF) {
			// r 回到当前行的开头
			// n 下一行的开头
			if (ch == '\r' || ch == '\n') {
				/*cout << tmp << endl;*/
				if (tmp.empty()) continue;
				{
					if (func) {
						func(tmp);
					}
					else {
						lock_guard<mutex> lock(m_mtx);
						m_outs.push(tmp);
					}
				}
				tmp = "";
				continue;
			}
			tmp += ch;
		}
		_pclose(fp);
		is_running = false;
		return true;
		});
	
	return true;
}

bool XExec::getOutput(string& out)
{
	lock_guard<mutex> lock(m_mtx);
	if (m_outs.empty()) return false;
	out = move(m_outs.front());
	m_outs.pop();
	return true;
}


