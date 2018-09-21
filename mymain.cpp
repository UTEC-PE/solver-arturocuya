#include <iostream>
#include "solver.h"
#include <map>
using namespace std;

int main(int argc, char const *argv[]) {

  Solver<string>* solver = new Solver<string>();
  // string myStr="7/4*((a+b)*a)+3";
  // string myStr="7/4*((a+-+--b)*a)+3";
  // string myStr="2+(3)";
  string myStr="7/4*((a+b)^4*a)+3";

  cout << solver->solve(myStr) << endl;

  return 0;
}
