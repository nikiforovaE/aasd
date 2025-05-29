#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include "2-3Tree.h"
#include "2-3Set.h"
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
    nikiforova::Tree< std::string, nikiforova::TreeSet< std::string > > dict = nikiforova::readAllDictsFromStream(fInput);
    using command_t = std::function< void(std::string&, nikiforova::DictOfDicts&) >;
    using constCommand_t = std::function< void(std::string&, const nikiforova::DictOfDicts&) >;

    nikiforova::Dictionary< std::string, command_t > commands
    {
      {"complement", nikiforova::complement},
      {"intersect", nikiforova::intersect},
      {"union", nikiforova::myUnion}
    };
    nikiforova::Dictionary< std::string, constCommand_t > constCommands
    {
      {"print", nikiforova::print},
      {"words", nikiforova::wordsWithPrefix},
      {"contain", nikiforova::contain},
      {"save", nikiforova::save}
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
        auto cIter = constCommands.find(command);
        if (cIter == constCommands.end())
        {
          std::string temp = "";
          std::getline(std::cin, temp);
          nikiforova::invalidCommandMessage(std::cout);
          std::cout << "\n";
        }
        else
        {
          std::string str = "";
          std::getline(std::cin, str);
          cIter->second(str, dict);
        }
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
