#pragma once
#include <string>

/// <summary>
/// 音视频任务处理接口
/// </summary>
class XTask {
public:
	struct Data {
		std::string type; // 任务类型 cv play
		std::string src; // 源文件
		std::string des; // 目标文件
		std::string password; // 加解密密钥
		int begin_sec{ 0 }; // 剪切开始时间
		int end_sec{ 0 }; // 剪切结束时间，0表示到达视频结尾
		bool is_enc{ true }; // 是否加密
	};

	/// <summary>
	/// 开始音视频处理任务，立即返回，线程中处理
	/// </summary>
	/// <param name="">任务配置参数</param>
	/// <returns>任务是否正常执行</returns>
	virtual bool start(const Data&) = 0;

	/// <summary>
	/// 判断任务是否处理完成
	/// </summary>
	/// <returns></returns>
	virtual bool running() = 0;

	/// <summary>
	/// 获取任务进度，0~100%
	/// </summary>
	/// <returns>0~100进度值</returns>
	virtual int progress() = 0;

	/// <summary>
	/// 视频总时长（秒）
	/// </summary>
	/// <returns></returns>
	virtual int totalSec() = 0;

	virtual void clear() = 0;
};