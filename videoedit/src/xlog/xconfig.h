#pragma once
#include <map>
#include <string>

// Read simple key=value config file.
class XConfig {
public:
	// Read config file into internal map.
	bool read(const std::string& config);

	// Get value by key (returns empty string when missing).
	std::string get(const std::string& key) const;

private:
	std::map<std::string, std::string> m_conf;
};

