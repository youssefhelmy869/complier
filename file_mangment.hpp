// file_mangment.hpp
#include <iostream>
#include <fstream>
#include <string>
#pragma once

using namespace std;

inline string read_file(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "error could not open file" << filename;
        return "";
    }
    string code((istreambuf_iterator<char>(file)),
                istreambuf_iterator<char>()

    );
    return code;
}

void overwriteFileWithString(const std::string &content, const std::string &filename)
{
    std::ofstream file(filename, std::ios::trunc); // Open in truncate mode to delete existing content
    if (!file)
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
}

void appendToFileWithNewLine(const std::string &content, const std::string &filename)
{
    std::ofstream file(filename, std::ios::app); // Open in append mode
    if (!file)
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    file << content << std::endl; // Add content followed by a newline
    file.close();
}