#include <iostream>
#include "lexser.hpp"

using namespace std;

int main() {
    
    lexser lx("code.txt");
    lx.lex();
    lx.debug_lexser_output();
    
    cout<<"[main] exiting\n";
    return 0;
}