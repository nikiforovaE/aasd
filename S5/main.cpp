#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "dictionary.h"
#include "commandsWithDictsOfDicts.h"
#include "errorMessages.h"
#include "2-3Tree.h"
#include "functors.h"
#include "commandsS5.h"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Incorrect number of arguments";
    return 1;
  }
  std::ifstream fInput(argv[2]);
  if (!fInput)
  {
    std::cerr << "File open error";
    return 1;
  }
  try
  {
    std::string traversType = argv[1];
    std::string data;
    std::getline(fInput, data);
    fInput.close();
    nikiforova::Tree< long long, std::string > tree = nikiforova::convertStringToDict(data);
    if (tree.isEmpty())
    {
      nikiforova::emptyMessage(std::cout);
      return 0;
    }
    nikiforova::Key_value_summ sum;
    using Summ = nikiforova::Key_value_summ;
    using command_t = std::function < Summ(nikiforova::Dict&, Summ&) >;
    nikiforova::Dictionary< std::string, command_t > commands
    {
      {"ascending", nikiforova::traverseLnr},
      {"descending", nikiforova::traverseRnr},
      {"breadth", nikiforova::traverseBreadth}
    };
    auto iter = commands.find(traversType);
    if (iter == commands.end())
    {
      nikiforova::invalidCommandMessage(std::cout);
      return 1;
    }
    else
    {
      iter->second(tree, sum);
      std::cout << sum.getResultSumm() << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
