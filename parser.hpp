// parser.hpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include "file_mangment.hpp"
#include "lexser.hpp"
#include "statments.hpp"
#pragma once

ofstream create_assembly_file(string name = "output\\output.asm") //
{
    ofstream asmfile(name);
    if (!asmfile.is_open())
    {
        cerr << "Failed to open file " << name << endl;
    }
    return asmfile;
}
