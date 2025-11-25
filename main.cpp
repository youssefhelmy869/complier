#include <iostream>
#include "lexser.hpp"
#include "errorchecker.hpp"
#include "parser.hpp"

using namespace std;

int main()
{

    lexser lx("output\\code.txt");
    lexsed_file *file_to_paras = lx.toknize(true);
    debug_lexsed_file(file_to_paras);
    check_for_error(file_to_paras);

    cout << "[main] exiting\n";
    return 0;
    
}