#include <iostream>
#include "fftask.h"
#include "xexec.h"
#include "log_factory.h"

using namespace std;
#define DEFAULTPASS "0123456789ABCDEF0123456789ABCDEF"

static int timeToSec(const string& s) {
    if (s.size() < 8) return 0;
    int hour = 0;
    int min = 0;
    int sec = 0;
    try {
        hour = stoi(s.substr(0, 2));
        min = stoi(s.substr(3, 2));
        sec = stoi(s.substr(6, 2));
    }
    catch (const std::exception&) {

    }
    
    return hour * 3600 + min * 60 + sec;
}

bool FFTask::start(const Data& para)
{
    cout << "\033[1;33m" << "+---------------------------------------------+" << endl;
    cout << "| [>] PROCESSING FFTASK START | PLEASE WAIT...|" << endl;
    cout << "+---------------------------------------------+" << "\033[0m" << endl;
    
    string cmd = "ffmpeg -y";
    if (para.type == "play") {
        cmd = "ffplay";
    }

    ///////////////////////////////////////////////
    // 视频剪切
    if (para.begin_sec > 0) {
        cmd += " -ss " + to_string(para.begin_sec);
    }
    if (para.end_sec > 0) {
        int t = para.end_sec - para.begin_sec;
        if (t > 0) {
            cmd += " -t " + to_string(t);
        }
    }
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // 视频解密
    if (!para.is_enc) {
        if (!para.password.empty()) {
            string pass = DEFAULTPASS;
            for (int i = 0; i < para.password.size() && i < pass.size(); ++i) {
                pass[i] = para.password[i];
            }
            cmd += " -decryption_key ";
            cmd += pass;
        }
    }
    /////////////////////////////////////////////

    // 输入文件
    cmd += " -i " + para.src;

    /////////////////////////////////////////////
    // 视频加密
    if (!para.password.empty() && para.is_enc) {
        string pass = DEFAULTPASS;
        cmd += " -encryption_scheme cenc-aes-ctr -encryption_kid 0123456789ABCDEF0123456789ABCDEF";
        cmd += " -encryption_key ";
        for (int i = 0; i < para.password.size() && i < pass.size(); ++i) {
            pass[i] = para.password[i];
        }
        cmd += pass;
    }
    ////////////////////////////////////////////

    // 输出文件
    if (!para.des.empty()) {
        cmd += " " + para.des;
    }
    ////////////////////////////////////////////
    string cmdLog = cmd;
    if (!para.password.empty()) {
        auto pos = cmdLog.find(para.password);
        if (pos != string::npos) {
            cmdLog.replace(pos, para.password.size(), string(para.password.size(), '*'));
        }
    }
    /*cout << "cmd: " << cmd << endl;*/
    LOGINFO("ffmpeg cmd: " + cmdLog);
    
    m_exec.start(cmd.c_str(), [this](const string& str) {
        /*cout << str << endl;*/
        // 1.获取视频时长
        {
            if (m_total_sec <= 0) {
                auto pos = str.find("Duration: ");
                if (pos != string::npos) {
                    string tmp = str.substr(pos + 10, 8);
                    /*cout << tmp << endl;*/
                    m_total_sec = timeToSec(tmp);
                    /*cout << "total_sec = " << totalSec() << "s" << endl;*/
                    return;
                }
            }
        }
        // 2.获取进度
        {
            auto pos = str.find("time=");
            if (pos != string::npos) {
                string tmp = str.substr(pos + 5, 8);
                int prs = timeToSec(tmp);
                if (m_total_sec > 0) {
                    m_progress = prs * 100 / m_total_sec;
                    return;
                }
            }
        }
        });
    return true;
}
