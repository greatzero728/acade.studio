#include <iostream>
using namespace std;

int main(){
    for(int i = 0; i < 9; i++)
        cout << i << "??<>" << i + 1 << "\n";
    cout << "9??>>??0\n";
    cout << "??<>1\n";
    for(int i = 0; i <= 9; i++)
        cout << "?" << i << ">>" << i << "?\n";
    cout << "?>>??\n";
    cout << ">>?";
    return 0;
}