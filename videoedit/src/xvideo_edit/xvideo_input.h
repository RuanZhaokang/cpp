#pragma once
#include <memory>
#include "xtask.h"

// Accepts user input and executes video tasks.
class XVideoInput {
public:
	// Interactive mode: read commands from stdin until "exit".
	void start(std::unique_ptr<XTask> task);

private:
	void runTask(XTask& task, const XTask::Data& data);
};
