#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "xlog.h"
#include "log_factory.h"

class XLOG_API UserInput {
public:
	// Start interactive console loop.
	void start(std::function<void(std::vector<std::string>)> init = [](std::vector<std::string>) {});

	void stop() {
		is_exit = true;
	}

	// Register option handler, e.g. "-s", "-d".
	UserInput& reg(std::string key, std::function<void(const std::string&)> func) {
		m_funcs[key] = func;
		return *this;
	}

	// Register task handler, e.g. "cv", "play".
	UserInput& regTask(std::string key, std::function<void()> func) {
		m_task_funcs[key] = func;
		return *this;
	}

private:
	bool is_exit = false;
	std::map<std::string, std::function<void(const std::string&)>> m_funcs;
	std::map<std::string, std::function<void()>> m_task_funcs;
};
