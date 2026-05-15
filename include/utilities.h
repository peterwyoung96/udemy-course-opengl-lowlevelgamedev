#pragma once

/**
 * @file utilities.h
 * @date 2026-05-14
 * @author Peter Young
 * 
 * @brief Helper functions
 */

// // HEADERS //////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <glad/glad.h>

// // NAMESPACE ////////////////////////////////////////////////////////////////

inline char* readFileContents(const char *source)
{
    // TRY AND OPEN THE FILE. EXIT IF IT DOESN'T WORK.
    std::ifstream file;
    file.open(source);

    if (!file.is_open())
    {
        std::cout << "Error opening file: " 
            << source << "\n";
        return nullptr;
    }

    // GET THE SIZE OF THE FILE BY MOVING TO THE END OF
    // IT AND GETTING THE "BIT ID?" (NOT SURE WHAT TO CALL IT)
    // MAKE SURE TO GO BACK TO THE START OF THE FILE.
    GLint size = 0;
    file.seekg(0, file.end);
    size = file.tellg();
    file.seekg(0, file.beg);

    char *fileContent = new char[size+1] {};
    file.read(fileContent, size);
    file.close();

    return fileContent;

} // end-readFileContents

// // EOF //////////////////////////////////////////////////////////////////////