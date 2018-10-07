#include <iostream>
#include "solver.h"
#include <map>
using namespace std;

// Puedes llamar a tu functión desde la termina ./solver "5-3"
int main(int argc, char const *argv[]) {
    // Te falta controlar mejor el menos unario: e.g. -(5+3)
    string myStr;
    if (argc == 2) {
        myStr = argv[1];
    }
    else {
      throw "One argument expected";
    }

    Solver<string>* solver = new Solver<string>();
    // string myStr="7/4*((a+b)*a)+3";
    // string myStr="7/4*((a+-+--b)*a)+3";
    // string myStr="2+(3)";
    //string myStr="7/4*((a+b)^4*a)+3";
    //string myStr = "(17*3/2-a)^b";

    cout << solver->solve(myStr) << endl;

    return 0;
}
