#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "user_input.h"

using namespace std;

static vector<string> split(const string& str) {
	string tmp;
	istringstream iss(str);
	vector<string> res;
	while (getline(iss, tmp, ' ')) {
		if (tmp.empty()) continue;
		res.push_back(tmp);
	}
	return res;
}

void UserInput::start(std::function<void(std::vector<std::string>)> init) {
	string input;
	while (!is_exit) {
		cout << "\n>>" << flush;
		getline(cin, input);
		if (input.empty()) continue;
		if (input == "exit") break;

		auto vec = split(input);
		if (vec.empty()) continue;

		string type = vec[0];

		// 1) init
		init(vec);

		// 2) parse options
		for (int i = 1; i < vec.size(); ++i) {
			auto& key = vec[i];
			auto fit = m_funcs.find(key);
			if (m_funcs.find(key) != m_funcs.end()) {
				if (vec.size() - 1 > i) {
					auto& value = vec[i + 1];
					if (m_funcs.find(value) == m_funcs.end()) {
						cout << key << ":" << value << endl;
						fit->second(value);
						i++;
						continue;
					}
				}
				fit->second("");
			}
		}

		// 3) execute task
		LOGDEBUG("UserInput receive: " + input);
		auto task = m_task_funcs.find(type);
		if (task == m_task_funcs.end()) {
			LOGERROR("Unsupported command type: " + type);
			cout << "type: " << type << " not support!" << endl;
		}
		else {
			task->second();
		}
	}
}
