//#include "simulation.h"
//#include "molecule.h"
//#include "typemolecule.h"
//#include "reaction.h"
#include "parser.tab.hpp"

int main(int argc, char** argv) {
  parser.tab::yyparse();
  return 0;
}
