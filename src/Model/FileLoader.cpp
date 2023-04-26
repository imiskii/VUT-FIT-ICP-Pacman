/**
 * @file FileLoader.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief functions that operate with files that are used by application
 * 
 */


#include "FileLoader.h"


using namespace  std;


vector<string> LoadFileNamesFromDir(const char *dirPath, const char *fileExt)
{
    int extLen = strlen(fileExt);
    vector<string> files;
    // Iterate through files in given directory
    // Reference can not be used because it have to modify fileName and store it in vector
    for (auto file : filesystem::directory_iterator(dirPath))
    {
        string fileName = file.path().filename().string();  // make the file name as string type
        size_t dotIndex = fileName.find(".");               // finde start of file extension
        if (dotIndex != string::npos)                       // Check for files with no extension
        {
            if (fileName.substr(dotIndex+1, extLen) == fileExt) // save only files with given extension
            {
                files.push_back(fileName.erase(dotIndex));
            }
        }
    }
    return files;
}
