#include "commandsS5.h"

nikiforova::Key_value_summ nikiforova::traverseLnr(Dict& dict, Key_value_summ& sum)
{
  return sum = dict.traverse_lnr(sum);
}

nikiforova::Key_value_summ nikiforova::traverseRnr(Dict& dict, Key_value_summ& sum)
{
  return sum = dict.traverse_rnl(sum);
}

nikiforova::Key_value_summ nikiforova::traverseBreadth(Dict& dict, Key_value_summ& sum)
{
  return sum = dict.traverse_breadth(sum);
}
