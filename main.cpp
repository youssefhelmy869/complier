#include <iostream>
#include "lexser.hpp"

using namespace std;

int main() {
    
    lexser lx("code.txt");
    lexsed_file * file_to_paras = lx.toknize(true);
    
    cout<<"[main] exiting\n";
    return 0;
}