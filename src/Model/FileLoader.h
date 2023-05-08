/**
 * @file FileLoader.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for FileLoader.cpp
 *
 */

#ifndef FILELOADER_H
#define FILELOADER_H


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>
#include <fstream>


using namespace std;

/**
 * @brief Load file names from given directory that have given file extension
 * @param dirPath path to directory with files
 * @param fileExt extension of file that
 * @return vector of strings with file names that have given file extension
 */
vector<string> LoadFileNamesFromDir(const char *dirPath, const char *fileExt);


/**
 * @brief read lines from given file
 * @param fileLines reference to vector where lines will be read
 * @param path path to file from which lines will be read
 * @return True if reading was successful else return False
 */
bool ReadLinesFromFile(vector<string> &fileLines, const char *path);


#endif // FILELOADER_H


/* END OF FILE */
