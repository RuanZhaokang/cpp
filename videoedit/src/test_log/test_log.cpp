#include <iostream>
#include "xlog.h"
#include "log_factory.h"
#include "xexec.h"
#include "user_input.h"

using namespace std;

int main()
{
    UserInput uip;
    uip
        // 注册参数处理函数
        .reg("-s", [](const string& str) {
            cout << "-----call src: " << str << endl;
        }).reg("-d", [] (const string& str){
            cout << "-----call des: " << str << endl;
        }).reg("-p", [](const string& str) {
            cout << "-----call pswd: " << str << endl;
        })
          // 注册任务处理函数
          .regTask("cv", [] {
            cout << "\033[1;33m" << "+--------------------------------------------+" << endl;
            cout << "| [>] PROCESSING CV TASK | PLEASE WAIT...    |" << endl;
            cout << "+--------------------------------------------+" << "\033[0m" << endl;
        });

    uip.start();
    
    return 0;
}