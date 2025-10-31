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
    NEW_LINE,
    DOT_OPERATOR,
    COLON_OPERTOR

};
struct Token
{
    TokenType Type;
    string text;
    int line_number;
};
constexpr unsigned long long hash(const char *str) // ascii based hash
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
    else if (type == TokenType::DOT_OPERATOR)
    {
        return "DOT_OPERATOR";
    }
    else if (type == TokenType::COLON_OPERTOR)
    {
        return "COLON_OPERTOP";
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
        case '\n':
            return TokenType::NEW_LINE;
        case '.':
            return TokenType::DOT_OPERATOR;
        case ':':
            return TokenType::COLON_OPERTOR;
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
    tok->Type = TokenType::IDENTFIER;
    return TokenType::IDENTFIER;
}
struct lexsed_file
{
    int number_of_lines;

    vector<Token *> token_list;
    int number_of_tokens;
    vector<Token *> function_idenfiers;
    vector<Token *> varablies;
    int number_of_statments;
};
class lexser
{
private:
    int number_of_lines = 0;
    vector<Token *> Token_list;
    int number_of_tokens = 0;
    int number_of_statments = 0;
    vector<Token *> function_identfiers;
    vector<Token *> varble_identfier;

    string code = " ";

public:
    lexser(string filename)
    {

        code = read_file(filename);
        if (code == " ")
        {
            cerr << "[LEXSER] file not found\n";
        }
        find_number_of_lines();
    }

private:
    inline void find_number_of_lines()
    {
        for (auto &ch : code)
        {
            if (ch == '\n')
            {
                ++number_of_lines;
            }
        }
        cout << "[LEXSER FIND NUMBER OF LINES FUNCTION] number of lines are " << number_of_lines << "\n";
    }

    void find_paramters()
    {
        cout<<"[LEXSER FIND PARAMTERS FUNCTION]find paramter function has been called\n";
        if (Token_list.size() == 0)
        {
            cout << "[LEXSER FIND PARAMTERS FUNCTION] the token list is empty\n";
        }
        size_t token_list_size = Token_list.size();
        int para_found = 0;
        
        for (size_t i = 0; i <= token_list_size; ++i)
        {
            if(i >= token_list_size){
                break;
            }
            if(i == 0){
                cout<<"iterntion 0 skiped\n";
                continue;

            }
            Token *tok = Token_list[i];
            if (tok->Type == TokenType::IDENTFIER && ((Token_list[i - 1]->Type == TokenType::BRACKET || Token_list[i - 1]->Type == TokenType::COMMA) && (Token_list[i + 1]->Type == TokenType::BRACKET || Token_list[i + 1]->Type == TokenType::COMMA)))
            {
                cout << "[LEXSER FIND PARAMTER FUNCTION] paramter " << tok->text << " has been found\n";
                tok->Type = TokenType::PRAMTER;
                ++para_found;
            }
        }
        if(para_found == 0){
            cout<<"[lexser find paramter function] no paramters found\n";
        }
    }

public:
    void debug_lexser_output()
    {
        cout << "====================== debuging lexser=====================\n";
        cout << "Token text   |   token type   |   line number \n";
        for (auto &tok : Token_list)
        {
            cout << tok->text << "           " << print_token_type(*tok) << "         " << tok->line_number << "\n";
        }
        cout << "============================================================\n";
        cout << "FUNCTION IDENTFIERS = " << function_identfiers.size();
        for (auto &tok : function_identfiers)
        {
            cout << "function identfier = " << tok->text << "\n";
        }
    }

private:
    void find_function_identfiers()
    {
        for (auto &tok : Token_list)
        {
            if (tok->Type == TokenType::FUNCTION_IDENTFIER)
            {
                function_identfiers.push_back(tok);
            }
        }
    }
    void find_varables()
    {
        int i = 0;
        for (auto &tok : Token_list)
        {
            if (i + 3 >= Token_list.size())
            {
                break;
            }
            if (tok->Type == TokenType::IDENTFIER && Token_list[i + 1]->Type == TokenType::ASSIGMENT_OPERATOR && Token_list[i + 3]->Type == TokenType::END_OF_STATMENT)
            {
                varble_identfier.push_back(tok);
            }

            ++i;
        }
    }
    int lex()
    { // exit code success 0
        cout << "[LEXSER LEX FUNCTION] lex function has started code is \n"
             << code << "\n";
        int current_line = 0;
        string word;
        bool in_string = false;

        for (int i = 0; i < code.length(); ++i)
        {
            char ch = code[i];
            cout << "[LEXSER LEX FUNCTION MAIN LOOP] ch = " << ch << "\n";
            if (ch == '\n')
            {
                ++current_line;
                continue;
            }
            if (ch == '"')
            {
                if (!in_string && !word.empty())
                {
                    Token *temp = new Token;
                    ++number_of_tokens;
                    temp->text = word;
                    temp->Type = find_token_type(temp);
                    temp->line_number = current_line;
                    Token_list.push_back(temp);
                    word.clear();
                    cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
                }
                word += ch;
                in_string = !in_string;
                if (!in_string)
                {
                    Token *temp = new Token;
                    ++number_of_tokens;
                    temp->text = word;
                    temp->Type = TokenType::IDENTFIER; // String literal
                    temp->line_number = current_line;
                    Token_list.push_back(temp);
                    word.clear();
                    cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
                }
                continue;
            }
            if (in_string)
            {
                word += ch;
                continue;
            }
            if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',' || ch == '.' || ch == ':')
            {

                if (!word.empty())
                {
                    Token *temp = new Token;
                    ++number_of_tokens;
                    temp->text = word;
                    temp->Type = find_token_type(temp);
                    temp->line_number = current_line;
                    Token_list.push_back(temp);
                    word.clear();
                    cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
                }

                // Check for double character operators (==)
                if (ch == '=' && i + 1 < code.length() && code[i + 1] == '=')
                {
                    Token *temp = new Token;
                    ++number_of_tokens;
                    temp->text = "==";
                    temp->Type = TokenType::COMP_OPERATOR_EQUAL;
                    temp->line_number = current_line;
                    Token_list.push_back(temp);
                    i++; // Skip next character
                    cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
                }
                else
                {
                    string op(1, ch);
                    Token *temp = new Token;
                    ++number_of_tokens;
                    temp->text = op;
                    temp->Type = find_token_type(temp);
                    temp->line_number = current_line;
                    Token_list.push_back(temp);
                    cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
                }
                continue;
            }

            // Handle whitespace
            if (isspace(ch))
            {
                if (!word.empty())
                {
                    Token *temp = new Token;
                    ++number_of_tokens;
                    temp->text = word;
                    temp->Type = find_token_type(temp);
                    temp->line_number = current_line;
                    Token_list.push_back(temp);
                    word.clear();
                    cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
                }
                continue;
            }

            word += ch;

            // Handle last token if exists

            if (in_string)
            {
                word += ch;
                continue;
            }
        }
        if (!word.empty())
        {
            Token *temp = new Token;
            ++number_of_tokens;
            temp->text = word;
            temp->Type = find_token_type(temp);
            temp->line_number = current_line;
            Token_list.push_back(temp);
            cout << "[LEXSER LEX FUNCTION] made new token number " << number_of_tokens << " token of " << temp->text << " was given type " << print_token_type(*temp) << "\n";
        }
        cout << "[lexser lex function] finised the main loop\n";
        string null_string = " ";
        overwriteFileWithString(null_string, "lexser_output.txt");
        overwriteFileWithString(null_string, "lexser_output_type.txt");

        for (auto &tok : Token_list)
        {

            cout << tok->text << "\n";
            appendToFileWithNewLine(tok->text, "lexser_output.txt");
            appendToFileWithNewLine(print_token_type(*tok), "lexser_output_type.txt");
        }

        // cheack if there is a entry point
        bool entry_point_found = false;
        for (auto &tok : Token_list)
        {
            if (tok->Type == TokenType::ENTERY_POINT)
            {
                entry_point_found = true;
                break;
            }
        }
        if (!entry_point_found)
        {
            cout << "[lexser] warning:\n";
            cout << "                  this file has no entry point (main:)\n";
        }
        cout << "number of tokens  = " << number_of_tokens << "\n";
        cout << "vector size = " << Token_list.size() << "\n";
        cout << "[lexser] exiting \n";

        return 0;
    }

public:
    lexsed_file *toknize(bool debug = false)
    {
        lex();
        
        find_function_identfiers();
        find_varables();
        find_number_of_lines();
        find_paramters();
        lexsed_file *lx_file = new lexsed_file;
        lx_file->token_list = Token_list;
        lx_file->function_idenfiers = function_identfiers;
        lx_file->number_of_statments = number_of_statments;
        lx_file->number_of_tokens = number_of_tokens;
        lx_file->varablies = varble_identfier;
        lx_file->number_of_lines = number_of_lines;
        if (debug)
        {
            debug_lexser_output();
        }
        cout << "[LEXSER] return lexed file\n";
        return lx_file;
    }
};