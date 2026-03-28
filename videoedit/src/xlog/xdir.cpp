#include <filesystem>
#include <iostream>
#include "xdir.h"

using namespace std;

std::vector<XFile> XDir::getFiles(const std::string& path)
{
    vector<XFile> files;
    auto it = filesystem::recursive_directory_iterator(path);
    // µü´úÄ¿Â¼
    for (auto &p : it) {
        if (p.is_directory()) continue;
        if (!p.is_regular_file()) continue;
        files.push_back(
            {
                p.path().filename().string(),
                p.path().string(),
                p.path().extension().string()
            }
        );
    }
    
    return files;
}

bool XDir::isDir(const std::string& path)
{
    return filesystem::is_directory(path);
}

bool XDir::createDir(const std::string& path) {
    return filesystem::create_directory(path);
}
