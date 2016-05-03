#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>

using namespace std;

namespace test
{
    void section(string name)
    {
        cout << endl;
        cout << "------ ----- ----- -----" << endl;
        cout << "- " << name << endl;
        cout << "------ ----- ----- -----" << endl;
    }
    
    void result(bool pass, string message)
    {
        cout << (pass ? "PASS" : "FAIL") << " ";
        cout << message << endl;
    }
}

#endif