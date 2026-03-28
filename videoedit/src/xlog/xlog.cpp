#include "xlog.h"
#include <iostream>

using namespace std;

// 这是导出变量的一个示例
XLOG_API int nxlog=0;

// 这是导出函数的一个示例。
XLOG_API int fnxlog(void)
{
    return 0;
}

// 这是已导出类的构造函数。
Cxlog::Cxlog()
{
    cout << "Create Cxlog" << endl;
    return;
}
