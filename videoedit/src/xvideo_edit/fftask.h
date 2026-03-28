#pragma once
#include "xtask.h"
#include "xexec.h"

/// <summary>
/// 基于ffmpeg及ffplay工具实现的音视频模块
/// </summary>
class FFTask : public XTask {
public:
	/// <summary>
	/// 开始音视频处理任务，立即返回，线程中处理
	/// </summary>
	/// <param name="">任务配置参数</param>
	/// <returns>任务是否正常执行</returns>
	bool start(const Data&) override;

	/// <summary>
	/// 获取任务进度，0~100%
	/// </summary>
	/// <returns>0~100进度值</returns>
	int progress() override {
		return m_progress;
	};

	/// <summary>
	/// 视频总时长（秒）
	/// </summary>
	/// <returns></returns>
	int totalSec() override {
		return m_total_sec;
	};

	/// <summary>
	/// 获取任务进度，0~100%
	/// </summary>
	/// <returns>0~100进度值</returns>
	bool running() override {
		return m_exec.running();
	};

	void clear() override {
		m_total_sec = 0;
		m_progress = 0;
	}

private:
	int m_total_sec{ 0 }; // 视频总时长
	int m_progress{ 0 }; // 视频进度
	XExec m_exec;
};

