#include "operationsWithStrings.h"

bool nikiforova::isNumber(const std::string& str)
{
  bool isNumber = 1;
  for (size_t i = 0; i < str.size(); i++)
  {
    if (!std::isdigit(str[i]) && !((str[i] == '-') && (i == 0)))
    {
      isNumber = 0;
    }
  }
  return isNumber;
}

std::string nikiforova::getWord(std::string& str)
{
  std::string word = "";
  if (str[0] == ' ')
  {
    str.erase(0, 1);
  }
  word = str.substr(0, str.find(" "));
  str = str.erase(0, str.find(" "));
  return word;
}



