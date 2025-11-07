#include <iostream>
#include "lexser.hpp"

using namespace std;

int main() {
    
    lexser lx("code.txt");
    lexsed_file * file_to_paras = lx.toknize(true);
    debug_lexsed_file(file_to_paras);
    cout<<"[main] exiting\n";
    return 0;
}