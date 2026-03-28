#include <iostream>
#include <fstream>
#include <cctype>
#include "xconfig.h"

using namespace std;

static inline void TrimInPlace(string& s) {
	auto is_space = [](unsigned char c) { return std::isspace(c) != 0; };
	while (!s.empty() && is_space(static_cast<unsigned char>(s.front()))) s.erase(s.begin());
	while (!s.empty() && is_space(static_cast<unsigned char>(s.back()))) s.pop_back();
}

bool XConfig::read(const std::string& config) {
	ifstream ifs(config);
	if (!ifs.is_open()) {
		return false;
	}

	string line;
	while (std::getline(ifs, line)) {
		TrimInPlace(line);
		if (line.empty()) continue;
		if (line[0] == '#') continue;
		if (line.rfind("//", 0) == 0) continue;

		auto pos = line.find('=');
		if (pos == string::npos || pos == 0) continue;

		auto key = line.substr(0, pos);
		auto value = line.substr(pos + 1);
		TrimInPlace(key);
		TrimInPlace(value);
		if (!key.empty()) {
			m_conf[key] = value;
		}
	}

	return true;
}

std::string XConfig::get(const std::string& key) const {
	auto res = m_conf.find(key);
	if (res == m_conf.end()) {
		return std::string();
	}
	return res->second;
}
