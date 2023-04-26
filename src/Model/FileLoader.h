/**
 * @file FileLoader.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for FileLoader.cpp
 * 
 */

#ifndef FILELOADER_H
#define FILELOADER_H


using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>


/**
 * @brief LoadFileNamesFromDir Lead file names from given directory that have given file extension
 * @param dirPath path to directory with files
 * @param fileExt extension of file that
 * @return vector of strings with file names that have given file extension
 */
vector<string> LoadFileNamesFromDir(const char *dirPath, const char *fileExt);


#endif // FILELOADER_H
