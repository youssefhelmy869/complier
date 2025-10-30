// lexser.hpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include "file_mangment.hpp"
#pragma once

using namespace std;

enum class TokenType
{
    ENTERY_POINT,
    ASSIGMENT_OPERATOR, // =
    KEYWORD,
    ARTHMETIC_OPERATOR_PLUS,  // +
    ARTHMETIC_OPERATOR_MINUS, // -
    ARTHMETIC_OPERATOR_MUL,   // * /
    ARTHMETIC_OPERATOR_DIV,   // /
    IDENTFIER,
    END_OF_STATMENT, // ;
    BRACKET,
    CURLYBRACKET,
    COMP_OPERATOR_EQUAL, // ==
    COMMENT,             // !
    END_COMMENT,         // $
    FUNCTION_IDENTFIER,
    UNKNOWN,
    COMMA,
    PRAMTER,
    NEW_LINE

};
struct Token
{
    TokenType Type;
    string text;
    int line_number;
};
inline constexpr unsigned long long hash(const char *str) // ascii based hash
{
    unsigned long long hash = 0;
    while (*str)
    {
        hash = (hash << 8) | static_cast<unsigned char>(*str);
        ++str;
    }
    return hash;
}

string print_token_type(Token &tok)
{
    TokenType &type = tok.Type;
    if (type == TokenType::ENTERY_POINT)
    {
        return "ENTRY_POINT";
    }
    else if (type == TokenType::END_OF_STATMENT)
    {
        return "END_OF_STATMENT";
    }
    else if (type == TokenType::BRACKET)
    {
        return "BRACKET";
    }
    else if (type == TokenType::IDENTFIER)
    {
        return "IDENTFIER";
    }
    else if (type == TokenType::ASSIGMENT_OPERATOR)
    {
        return "ASSIGMENT_OPERATOR";
    }
    else if (type == TokenType::KEYWORD)
    {
        return "KEYWORD";
    }
    else if (type == TokenType::ARTHMETIC_OPERATOR_PLUS)
    {
        return "ARTHMETIC_OPERATOR_PLUS";
    }
    else if (type == TokenType::ARTHMETIC_OPERATOR_MINUS)
    {
        return "ARTHMETIC_OPERATOR_MINUS";
    }
    else if (type == TokenType::ARTHMETIC_OPERATOR_MUL)
    {
        return "ARTHMETIC_OPERATOR_MUL";
    }
    else if (type == TokenType::ARTHMETIC_OPERATOR_DIV)
    {
        return "ARTHMETIC_OPERATOR_DIV";
    }
    else if (type == TokenType::CURLYBRACKET)
    {
        return "CURLYBRACKET";
    }
    else if (type == TokenType::COMP_OPERATOR_EQUAL)
    {
        return "COMP_OPERATOR_EQUAL";
    }
    else if (type == TokenType::COMMENT)
    {
        return "COMMENT";
    }
    else if (type == TokenType::END_COMMENT)
    {
        return "END_COMMENT";
    }
    else if (type == TokenType::FUNCTION_IDENTFIER)
    {
        return "FUNCTION_IDENTFIER";
    }
    else if (type == TokenType::COMMA)
    {
        return "COMMA";
    }
    else if (type == TokenType::PRAMTER)
    {
        return "PRAMTER";
    }
    else if (type == TokenType::NEW_LINE)
    {
        return "NEW_LINE";
    }

    else
    {
        cerr << "token " << tok.text << " not found\n";
        return " ";
    }
}
TokenType find_token_type(Token *tok)
{
    string token_text = tok->text;
    tok->Type = TokenType::IDENTFIER; // default type
    static bool function_identfier = false;

    // Handle single character tokens first
    if (token_text.length() == 1)
    {
        char c = token_text[0];
        switch (c)
        {
        case ';':
            return TokenType::END_OF_STATMENT;
        case '(':
        case ')':
            return TokenType::BRACKET;
        case '{':
        case '}':
            return TokenType::CURLYBRACKET;
        case '=':
            return TokenType::ASSIGMENT_OPERATOR;
        case '+':
            return TokenType::ARTHMETIC_OPERATOR_PLUS;
        case '-':
            return TokenType::ARTHMETIC_OPERATOR_MINUS;
        case '*':
            return TokenType::ARTHMETIC_OPERATOR_MUL;
        case '/':
            return TokenType::ARTHMETIC_OPERATOR_DIV;
        case '!':
            return TokenType::COMMENT;
        case '$':
            return TokenType::END_COMMENT;
        case ',':
            return TokenType::COMMA;
        }
    }

    // Handle multi-character tokens
    switch (::hash(token_text.c_str()))
    {
    case ::hash("main"):
    case ::hash(":"):
    case ::hash("main:"):
        cout << "entry point found\n";
        return TokenType::ENTERY_POINT;
    case ::hash("=="):
        return TokenType::COMP_OPERATOR_EQUAL;
    case ::hash("if"):
    case ::hash("else"):
    case ::hash("while"):
    case ::hash("for"):
        return TokenType::KEYWORD;
    case ::hash("def_f"):
        // the next identifier is a function name
        function_identfier = true;
        cout << "def_f keyword found\n";
        return TokenType::KEYWORD;
    case ::hash("return"):
        return TokenType::KEYWORD;
    }

    // If no specific type was found, it's an identifier
    cout << "token " << tok->text << " has been assigned type IDENTFIER\n";
    if (function_identfier == true)
    {
        // reset the flag before returning so it doesn't persist
        cout << "function identfeir found\n";
        function_identfier = false;
        return TokenType::FUNCTION_IDENTFIER;
    }

    return TokenType::IDENTFIER;
}
struct lexsed_file
{
    int number_of_lines;
    ofstream file;
    vector<Token *> token_list;
};
class lexser
{
    int number_of_lines = 0;
    vector<Token *> Token_list;

    string code = " ";

    lexser(string filename)
    {
        code = read_file(filename);
        if (code == " ")
        {
            cerr << "[LEXSER] file not found\n";
        }
        find_number_of_lines();
    }

    inline void find_number_of_lines()
    {
        for (auto &ch : code)
        {
            if (ch == '\n')
            {
                ++number_of_lines;
            }
        }
    }
    inline int find_paramters()
    {
        if (Token_list.size() == 0)
        {
            cout << "[LEXSER FIND PARAMTERS FUNCTION] the token list is empty\n";
        }
        for (int i = 0; i <= Token_list.size(); ++i)
        {
            Token *tok = Token_list[i];
            if (tok->Type == TokenType::IDENTFIER && (Token_list[i - 1]->Type == TokenType::BRACKET || Token_list[i - 1]->Type == TokenType::COMMA))
            {
                tok->Type == TokenType::PRAMTER;
            }
        }
    }
};