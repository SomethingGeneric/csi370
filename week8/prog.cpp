// Matt C 10-19-25
// CSI 370 w/ Brian Hall
// Assignment 8.1 Cylinder volume

#include <iostream>
using namespace std;

extern "C" void _asmMain();

extern "C" double _getDouble() {
    double d;
    std::cin >> d;
    return d;
}

extern "C" void _printString(char* s) {
    std::cout << s;
    return;
}

extern "C" void _printDouble(double d) {
    cout << d << endl;
}

// main stub driver
int main() {
    _asmMain();
    return 0;
}