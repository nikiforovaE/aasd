#include <iostream>
#include <fstream>
#include <string>
#include <list.h>
#include "stack.h"
#include "queue.h"
#include "expressionPart.h"
#include "expression_calculation.h"

int main(int argc, char** argv)
{
  std::ifstream fInput;
  if (argc == 2)
  {
    fInput.open(argv[1]);
    if (!fInput)
    {
      std::cerr << "File open error";
      return 1;
    }
  }
  std::istream& in = (argc == 2) ? fInput : std::cin;
  nikiforova::Stack< long long > result;
  std::string str;
  while (std::getline(in, str))
  {
    if (str == "")
    {
      continue;
    }
    try
    {
      result.push(nikiforova::calculate(str));
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what();
      return 1;
    }
  }
  if (!result.isEmpty())
  {
    std::cout << result.getTop();
    result.drop();
    while (!result.isEmpty())
    {
      std::cout << " " << result.getTop();
      result.drop();
    }
  }
  std::cout << "\n";
  return 0;
}
