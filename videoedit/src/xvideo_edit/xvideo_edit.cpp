#include <iostream>
#include <memory>
#include "xtask_factory.h"
#include "xvideo_input.h"
#include "xdir.h"
#include "xlog.h"
#include "log_factory.h"

using namespace std;

int main(int argc, char* argv[])
{
    LOGINIT();
    LOGINFO("Xvideo_edit start");

    XVideoInput input;
    input.start(XTaskFactory::create());

    LOGINFO("Xvideo_edit exit");
    
    return 0;
}
