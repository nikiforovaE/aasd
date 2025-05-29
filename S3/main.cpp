#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "bidirectionalList.h"
#include "dictionary.h"
#include "commandsWithDictsOfLists.h"
#include "errorMessages.h"

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
    nikiforova::Dictionary< std::string, nikiforova::BidirectionalList< long long > > dict = nikiforova::readAllLists(fInput);
    fInput.close();
    nikiforova::Dictionary< std::string, std::function< void(std::string&, nikiforova::DictOfLists&) > > commands
    {
      {"print", nikiforova::print},
      {"replace", nikiforova::replace},
      {"remove", nikiforova::remove},
      {"concat", nikiforova::concat},
      {"equal", nikiforova::equal}
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
