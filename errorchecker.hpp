// lexser.hpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include "file_mangment.hpp"
#include "lexser.hpp"
#pragma once

using namespace std;

inline void print_error(string error_message, int line_number)
{
    cout << "[ERROR FOUND] " << error_message << " at line " << line_number << "\n";
}
inline void print_com_f()
{
    cout << "\n";
    cout << "COMPLITION FAIL \n";
    cout << "return code -1\n";
    cout << "\n";
}
int check_for_error(lexsed_file *ls_file)
{

    cout << "===========================================================================================\n";
    cout << "=                                                                                         =\n";
    cout << "=                    looking for error function has started                               =\n";
    cout << "=                                                                                         =\n";
    cout << "===========================================================================================\n";

    int i = 0;
    for (auto &tok : ls_file->token_list)
    {
        if (i + 2 >= ls_file->token_list.size())
        {
            break;
        }
        if (tok->Type == TokenType::FUNCTION_IDENTFIER)
        {
            if (ls_file->token_list[i + 1]->Type != TokenType::BRACKET)
            {

                print_error("function idenfier sytax error", tok->line_number);

                print_error("no bracket after function idenftier", tok->line_number);
                print_com_f();
                return -1;
            }
        }
        else if (tok->Type == TokenType::KEYWORD && tok->text == "def_f")
        {
            if (ls_file->token_list[i + 1]->Type != TokenType::FUNCTION_IDENTFIER || ls_file->token_list[i + 2]->Type != TokenType::BRACKET)
            {
                print_error("keyowrd (def_f) has a wrong syntax", tok->line_number);

                print_com_f();
                return -1;
            }
        }
        else if (tok->Type == TokenType::KEYWORD && tok->text == "if")
        {
            if (ls_file->token_list[i + 1]->Type != TokenType::BRACKET)
            {
                print_error("error in if statment ", tok->line_number);
                print_com_f();
                return -1;
            }
        }
        
        ++i;
    }
    cout << "NO ERROR FOUND\n";
    return 0;
}