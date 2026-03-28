#include <iostream>
#include "xvideo_input.h"
#include "user_input.h"
#include "xdir.h"
#include "log_factory.h"

using namespace std;

void XVideoInput::start(std::unique_ptr<XTask> task) {
	LOGINFO("__FUNCSIG__ " + (string)__FUNCSIG__);

	UserInput user;
	XTask::Data data;

	// Register video processing task.
	user.regTask("cv", [&] {
		LOGINFO("Register task: cv task" + data.src + " " + data.des);
		data.type = "cv";

		// Src is a directory: process every file.
		if (XDir::isDir(data.src)) {
			XDir dir;
			auto files = dir.getFiles(data.src);
			for (auto f : files) {
				XTask::Data d = data;
				d.src = f.path;
				if (!XDir::isDir(data.des)) {
					XDir::createDir(data.des);
				}
				d.des = data.des + "/" + f.filename;
				task->clear();
				runTask(*task, d);
			}
		}
		else {
			runTask(*task, data);
		}
	})
		.reg("-s", [&](const string& src) {
			LOGINFO("Register parameter -s: " + src);
			data.src = src;
		})
		.reg("-d", [&](const string& des) {
			LOGINFO("Register parameter -d: " + des);
			data.des = des;
		})
		.reg("-b", [&](const string& begin) { // begin seconds
			LOGINFO("Register parameter -b: " + begin);
			data.begin_sec = stoi(begin);
		})
		.reg("-e", [&](const string& end) { // end seconds
			LOGINFO("Register parameter -e: " + end);
			data.end_sec = stoi(end);
		})
		.reg("-p", [&](const string& pswd) { // encrypt
			LOGINFO("Register parameter -p: " + pswd);
			if (pswd.empty()) {
				cout << "password: " << flush;
				string pass;
				cin >> pass;
				data.password = pass;
			}
			else {
				data.password = pswd;
			}
		})
		.reg("-dp", [&](const string& pswd) { // decrypt
			LOGINFO("Register parameter -dp: " + pswd);
			if (pswd.empty()) {
				cout << "password: " << flush;
				string pass;
				cin >> pass;
				data.password = pass;
			}
			else {
				data.password = pswd;
				data.is_enc = false;
			}
		});

	// Register play task.
	user.regTask("play", [&] {
		data.type = "play";
		task->start(data);
	});

	user.start([&](vector<string> para) {
		LOGINFO("UserInput start");

		data = XTask::Data();
		if (para.size() < 4) {
			if (para.size() > 1) {
				data.src = para[1];
			}
			if (para.size() > 2) {
				data.des = para[2];
			}
		}
	});
}

void XVideoInput::runTask(XTask& task, const XTask::Data& data) {
	LOGINFO("RunTask start: " + data.src + " -> " + data.des);
	task.start(data);

	int p = 0;
	int l = -1;
	while (task.running()) {
		p = task.progress();
		if (p != l) {
			cout << "\r" << "Progress: " << task.progress() << "%";
			l = p;
		}
	}
	cout << "\r" << "Progress: " << "100%" << endl;
	LOGINFO("Run task finished!");
}
