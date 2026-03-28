#pragma once
#include <memory>
#include "xtask.h"

/// <summary>
/// 创建XTask对象
/// </summary>
class XTaskFactory {
public:
	static std::unique_ptr<XTask> create(int type = 0);
};

