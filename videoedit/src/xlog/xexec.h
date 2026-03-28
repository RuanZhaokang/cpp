#pragma once
#include <string>
#include <queue>
#include <future>
#include <mutex>
#include "xlog.h"

class XLOG_API XExec {
public:
	/// <summary>
	/// 执行外部进程
	/// </summary>
	/// <param name="cmd">控制台命令</param>
	/// <param name="func">控制台输出回调，设置后不写入缓存队列</param>
	/// <returns>打开命令管道是否成功</returns>
	bool start(const char* cmd, std::function<void(const std::string&) > func);

	/// <summary>
	/// 判断任务是否执行
	/// </summary>
	/// <returns></returns>
	bool running() {
		return is_running;
	};

	/// <summary>
	/// 获取控制台输出
	/// </summary>
	/// <param name="out">输出到out</param>
	/// <returns>是否取到输出</returns>
	bool getOutput(std::string& out);

	bool wait() {
		return m_future.get();
	}

private:
	bool is_running = false;
	// 缓存队列
	std::queue<std::string> m_outs;
	// 任务执行线程
	std::future<bool> m_future;
	// 互斥访问锁
	std::mutex m_mtx;
};

