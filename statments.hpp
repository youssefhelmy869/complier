// satments.hpp
#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include "file_mangment.hpp"
#include "lexser.hpp"
#pragma once

using namespace std;

enum class statment_type
{
    ARTHMETIC_OPERTION,
    VARABLE_DECLARTION,
    VARABLE_EDITING,
    FUNCTION_CALL,
    FOR_LOOP,
    WHILE_LOOP,
    MAIN_FUNTION,
    FUNTION_DECLARTION,
    IF_CONDITION

};

struct condition
{
    int number;
    Token *logical_opertor;
    Token *operand1;
    Token *operand2;
};
struct arthetic_opertion
{
    int number;
    string athemtic_opertor;
    Token *operand1;
    Token *operand2;
    Token *result;
};

struct varable_declartion
{
    int number;
    Token *var;
    Token *value;
};
struct varable_editing
{
    int number;
    Token *varable_name_to_save_to;
    Token *value;
};
struct funtion_call
{
    int number;
    Token *funtion_to_call;
    vector<Token *> parameters;
};
struct for_loop
{
    int number;
    Token *iterantion_varable;
    vector<Token *> code_to_loop;
    Token *start_value;
    Token *end_value;
};
struct while_loop
{
    int number;
    condition loop_condition;
    vector<Token *> loop_code;
};

struct funtion_decleration
{
    int number;
    Token *funtion_name;
    vector<Token *> funtion_code;
    vector<Token *> paramters;
};
struct If_condition
{
    int number;
    condition If_condition;
    vector<Token *> if_code;
    vector<Token *> else_code;
};

using statmentData = variant<condition,
                             arthetic_opertion,
                             varable_declartion,
                             varable_editing,
                             funtion_call,
                             for_loop,
                             while_loop,
                             funtion_decleration,
                             If_condition>;
class statment_finder
{
private:
    condition make_condition(int i)
    {
        cout << "[statment finder] make condition funton called\n";
        condition temp;
        temp.number = statment_number;
        ++statment_number;
        // takes the iput the index of the conditional oprtor
        temp.logical_opertor = tokens[i];
        temp.operand1 = tokens[i - 1];
        temp.operand2 = tokens[i + 1];
        cout << "[statment finder] thsi condtion is number " << temp.number << " logaical oopertaor " << temp.logical_opertor->text << "\n";
        cout << "     operand 1 = " << temp.operand1->text << "\n";
        cout << "     operand 2 = " << temp.operand2->text << "\n";
        return_data.push_back(temp);
        return temp;
    }

    void make_arthemtic_opertion(int i)
    {
        // takes input i the ndex of the + - * /
        arthetic_opertion temp;
        temp.number = statment_number;
        ++statment_number;
        temp.athemtic_opertor = tokens[i]->text;
        temp.operand1 = tokens[i + 1];
        temp.operand2 = tokens[i - 1];
        temp.result = tokens[i - 3];
        return_data.push_back(temp);
    }

    void make_varable_declartion(int i)
    {
        varable_declartion temp;
        temp.number = statment_number;
        ++statment_number;
        // takes theput the index of the = token
        temp.var = tokens[i - 1];
        temp.value = tokens[i + 1];
        return_data.push_back(temp);
        varable_idenfiers.push_back(tokens[i - 1]);
    }

    void make_varable_editing(int i)
    {
        varable_editing temp;
        temp.number = statment_number;
        ++statment_number;
        // takes index of =
        temp.varable_name_to_save_to = tokens[i - 1];
        temp.value = tokens[i + 1];
        return_data.push_back(temp);
    }

    void make_funtion_call(int i)
    {
        // indes of funtion call identfier
        funtion_call temp;
        temp.number = statment_number;
        ++statment_number;
        temp.funtion_to_call = tokens[i];
        int i2 = i + 2;
        for (int index = 0; tokens[i2 + index]->Type == TokenType::BRACKET; ++index)
        {
            int i3 = index + i2;
            if (tokens[i3]->Type == TokenType::PRAMTER)
            {
                temp.parameters.push_back(tokens[i3]);
            }
        }
        cout << "[statment finder] funtion call created name is " << temp.funtion_to_call->text << " and parametsers are \n";
        for (auto &tok : temp.parameters)
        {
            cout << "parametr = " << tok->text << "\n";
        }
    }

    void make_for_loop(int i)
    {
        // the index of the for keyword
        for_loop temp;
        temp.number = statment_number;
        ++statment_number;
        temp.iterantion_varable = tokens[i + 2];
        temp.start_value = tokens[i + 4];
        temp.end_value = tokens[i + 6];
        int index = 9;
        int i2;
        for (auto &t : tokens)
        {
            i2 = index + i;
            Token *tok = tokens[i2];
            if (tok->Type != TokenType::CURLYBRACKET)
            {
                temp.code_to_loop.push_back(tok);
            }
            else
            {
                break;
            }
            ++index;
        }
        return_data.push_back(temp);
    }

    void make_while_loop(int i)
    {
        // input the while keyword index
        while_loop temp;
        temp.number = statment_number;
        ++statment_number;
        int index = i + 1;
        int comaprsion_index;
        for (auto &t : tokens)
        {
            Token *tok = tokens[index];

            if (tok->Type == TokenType::COMP_OPERATOR_EQUAL)
            {
                comaprsion_index = index;
                break;
            }
            ++index;
        }
        temp.loop_condition = make_condition(comaprsion_index);
    }

    void make_funtion_decleration(int i)
    {
        funtion_decleration temp;
        temp.number = statment_number;
        ++statment_number;
        // index of def_f
        temp.funtion_name = tokens[i + 1];
        // find paarters
        int index = i + 3;
        int bracket_index = i;
        for (auto &t : tokens)
        {
            if (tokens[index]->Type == TokenType::PRAMTER)
            {
                temp.paramters.push_back(tokens[index]);
            }
            else if (tokens[index]->Type == TokenType::BRACKET)
            {
                break;
            }

            ++index;
        }
        bracket_index = index - i;
        bracket_index = bracket_index + 2;

        // find code
        for (auto &t : tokens)
        {
            if (tokens[bracket_index]->Type == TokenType::CURLYBRACKET)
            {
                break;
            }
            else
            {
                temp.funtion_code.push_back(tokens[bracket_index]);
            }
            ++bracket_index;
        }

        return_data.push_back(temp);
    }

    void make_if__statment(int i)
    {
        If_condition temp;
        temp.number = statment_number;
        ++statment_number;
        int comp_index = 0;
        int index = i;
        for (auto &t : tokens)
        {
            if (tokens[index]->Type == TokenType::COMP_OPERATOR_EQUAL)
            {
                comp_index = index;
                break;
            }
            else
            {
                ++index;
            }
        }
        temp.If_condition = make_condition(comp_index);
        // find temp code and else code
        int curly_braket_index;
        index = i;
        while (index < tokens.size())
        {
            if (tokens[index]->Type == TokenType::CURLYBRACKET)
            {
                curly_braket_index = index;
                break;
            }
            ++index;
        }
        index = 0;
        index = curly_braket_index + 1;
        while (index < tokens.size())
        {
            if (tokens[index]->Type == TokenType::CURLYBRACKET)
            {
                break;
            }
            else
            {
                temp.if_code.push_back(tokens[index]);
            }
            ++index;
        }
        if (tokens[index + 1]->Type == TokenType::KEYWORD && tokens[index + 1]->text == "else")
        {
            int else_index = index + 1;
            int starting_curly_barcket = else_index + 1;
            index = starting_curly_barcket + 1;
            while (index < tokens.size())
            {
                if (tokens[index]->Type == TokenType::CURLYBRACKET)
                {
                    break;
                }
                else
                {
                    temp.else_code.push_back(tokens[index]);
                }
                ++index;
            }
        }
        return_data.push_back(temp);
    }

    int statment_number = 1;

    vector<Token *> tokens;
    vector<statmentData> return_data;
    int tokens_list_size;
    vector<Token *> varable_idenfiers;

public:
    statment_finder(vector<Token *> para_list)
    {
        tokens = para_list;
        return_data.reserve(tokens.size());
        tokens_list_size = tokens.size();
    }
    vector<statmentData> find_statment()
    {
        for (int i = 0; i >= tokens_list_size; ++i)
        {
            if (tokens[i]->Type == TokenType::ARTHMETIC_OPERATOR_DIV || tokens[i]->Type == TokenType::ARTHMETIC_OPERATOR_MINUS || tokens[i]->Type == TokenType::ARTHMETIC_OPERATOR_MUL || tokens[i]->Type == TokenType::ARTHMETIC_OPERATOR_PLUS)
            {
                make_arthemtic_opertion(i);
            }
            else if (tokens[i]->Type == TokenType::ASSIGMENT_OPERATOR)
            {
                bool is_a_varable = (find(varable_idenfiers.begin(), varable_idenfiers.end(), tokens[i]) != varable_idenfiers.end());
                if (is_a_varable == true)
                {
                    make_varable_editing(i);
                }
                else
                {
                    make_varable_declartion(i);
                }
            }

           
        }
    }
};

struct main_function
{
    vector<statmentData> statments;
};