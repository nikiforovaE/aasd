#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include "forwardList.h"
#include "2-3Tree.h"
#include "errorMessages.h"
#include "commandsWithDictsOfDicts.h"
#include "dictionary.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments";
    return 1;
  }
  std::ifstream fInput(argv[1]);
  if (!fInput)
  {
    std::cerr << "File open error";
    return 1;
  }
  try
  {
    nikiforova::Tree< std::string, nikiforova::Tree< long long, std::string > > dict = nikiforova::readAllDictsFromStream(fInput);
    nikiforova::Dictionary< std::string, std::function< void(std::string&, nikiforova::DictOfDicts&) > > commands
    {
      {"print", nikiforova::print},
      {"complement", nikiforova::complement},
      {"intersect", nikiforova::intersect},
      {"union", nikiforova::myUnion}
    };
    while (!std::cin.eof())
    {
      std::string command = "";
      std::cin >> command;
      if (command.empty())
      {
        continue;
      }
      auto iter = commands.find(command);
      if (iter == commands.end())
      {
        std::string temp = "";
        std::getline(std::cin, temp);
        nikiforova::invalidCommandMessage(std::cout);
      }
      else
      {
        std::string str = "";
        std::getline(std::cin, str);
        iter->second(str, dict);
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
  }
  return 0;
}
