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
    string varable_name_to_save_to;
    Token *value;
};
struct varable_editing
{
    int number;
    string varable_name_to_save_to;
    Token *value;
};
struct funtion_call
{
    int number;
    Token *funtion_to_call;
};
struct for_loop
{
    int number;
    string iterantion_varable;
    vector<Token *> code_to_loop;
    Token *start_value;
    Token *end_value;
};
struct while_loop
{
    condition *loop_condition;
    vector<Token *> loop_code;
};

struct funtion_decleration
{
    int number;
    Token *funtion_name;
    vector<Token *> funtion_code;
};
struct If_condition
{
    condition *If_condition;
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
    condition *make_condition(int i)
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
        return &temp;
    }

    arthetic_opertion *make_arthemtic_opertion(int i){
        //takes input i the ndex of the + - * /
        arthetic_opertion temp;
        temp.number = statment_number;
        ++statment_number;
        temp.athemtic_opertor = tokens[i] ->text;
        //temp.operand1
        return &temp;
    }
    int statment_number = 1;

    vector<Token *> tokens;
    vector<statmentData> return_data;

public:
    statment_finder(vector<Token *> para_list)
    {
        tokens = para_list;
    }
};

struct main_function
{
    vector<statmentData> statments;
};