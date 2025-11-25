//satments.hpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include "file_mangment.hpp"
#include "lexser.hpp"
#pragma once

enum class statment_type{
    ARTHMETIC_OPERTION,
    VARABLE_DECLARTION,
    VARABLE_EDITING,
    FUNCTION_CALL,
    FOR_LOOP,
    WHILE_LOOP,
    FOREACH_LOOP,
    MAIN_FUNTION
};

struct statment
{
    statment_type type;
    vector<Token *>tokens;
    
};
