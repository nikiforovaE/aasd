#ifndef COMMANDSS5_H
#define COMMANDSS5_H
#include "functors.h"
#include "commandsWithDictsOfDicts.h"
namespace nikiforova {

  Key_value_summ traverseLnr(Dict&, Key_value_summ&);
  Key_value_summ traverseRnr(Dict&, Key_value_summ&);
  Key_value_summ traverseBreadth(Dict&, Key_value_summ&);

}

#endif
