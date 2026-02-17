#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		cout << argv[i] << endl;
	}

	string fmt = "{context}-{file}:{line}"; // 日志模板格式
	if (argc > 2) {
		fmt = argv[2];
		cout << "fmt = " << fmt << endl;
	}
	string log = "test log context 001";
	cout << __FILE__ << ":" << __LINE__ << endl;

	string logstr = fmt; // 日志字符串
	string ckey{ "{context}" };
	auto pos = logstr.find(ckey);
	if (pos != string::npos) {
		logstr = logstr.replace(pos, ckey.size(), log);
	}

	string fkey{ "{file}" };
	pos = logstr.find(fkey);
	if (pos != string::npos) {
		logstr = logstr.replace(pos, fkey.size(), __FILE__);
	}

	string lkey{ "{line}" };
	pos = logstr.find(lkey);
	if (pos != string::npos) {
		logstr = logstr.replace(pos, lkey.size(), to_string(__LINE__));
	}

	cout << " ------------------- log -------------------- " << endl;
	cout << logstr << endl;

	return 0;
}
