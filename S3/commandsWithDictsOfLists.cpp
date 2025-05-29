#include "commandsWithDictsOfLists.h"
#include <string>
#include "errorMessages.h"
#include "operationsWithStrings.h"

nikiforova::DictOfLists nikiforova::readAllLists(std::istream& in)
{
  DictOfLists result;
  while (!in.eof())
  {
    std::string nameOfList = "";
    in >> nameOfList;
    DictOfLists::ConstIterator cIter = result.find(nameOfList);
    if (cIter != result.cend())
    {
      throw std::logic_error("List with the same name already exists");
    }
    else
    {
      std::string str = "";
      std::getline(in, str);
      nikiforova::BidirectionalList< long long > temp = nikiforova::convertStringToList(str);
      result.push(nameOfList, temp);
    }
  }
  return result;
}

nikiforova::BidirectionalList< long long > nikiforova::convertStringToList(std::string& str)
{
  BidirectionalList< long long > result;
  while (!str.empty())
  {
    long long value = 0;
    std::string temp = str.substr(1, str.find(" ", 1) - 1);
    if (!nikiforova::isNumber(temp))
    {
      throw std::logic_error("Value is not a number");
    }
    value = std::stoll(temp);
    str = str.erase(0, temp.length() + 1);
    result.pushBack(value);
  }
  return result;
}

void nikiforova::print(std::string&str , DictOfLists& dict)
{
  nikiforova::doPrint(std::cout, str, dict);
}

std::ostream& nikiforova::doPrint(std::ostream& out, std::string& str, DictOfLists dict)
{
  std::string nameOfList = nikiforova::getWord(str);
  if (nameOfList.empty())
  {
    return nikiforova::invalidCommandMessage(out);
  }
  nikiforova::BidirectionalList< long long > newList;
  DictOfLists::ConstIterator cIter = dict.find(nameOfList);
  if (cIter == dict.cend())
  {
    return nikiforova::invalidCommandMessage(out);
  }
  nikiforova::BidirectionalList< long long > temp = cIter->second;
  if (temp.isEmpty())
  {
    return nikiforova::emptyMessage(out);
  }
  out << nameOfList;
  for (auto&& pair: temp)
  {
    out << " " << pair;
  }
  out << "\n";
  return out;
}

void nikiforova::replace(std::string& str, DictOfLists& dict)
{
  int countArgs = 0;
  std::string nameOfList = nikiforova::getWord(str);
  if (!nameOfList.empty())
  {
    countArgs++;
  }
  nikiforova::DictOfLists::ConstIterator cIter = dict.find(nameOfList);
  if (cIter == dict.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::BidirectionalList< long long > newList;
  std::string arg1 = "";
  std::string arg2 = "";
  long long value = 0;
  if (!str.empty())
  {
    arg1 = nikiforova::getWord(str);
    countArgs++;
    if (!nikiforova::isNumber(arg1))
    {
      nikiforova::invalidCommandMessage(std::cout);
      return;
    }
    value = std::stoll(arg1);
    if (!str.empty())
    {
      arg2 = nikiforova::getWord(str);
      countArgs++;
    }
  }
  if (countArgs != 3)
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  if (nikiforova::isNumber(arg2))
  {
    long long newValue = std::stoll(arg2);
    nikiforova::doReplace(nameOfList, value, newValue, dict);
  }
  else
  {
    nikiforova::doReplace(nameOfList, value, arg2, dict);
  }
}

void nikiforova::doReplace(const std::string& nameOfList, long long value, long long newValue, DictOfLists& dict)
{
  nikiforova::BidirectionalList< long long > list = dict.get(nameOfList);
  for (auto&& item: list)
  {
    if (item == value)
    {
      item = newValue;
    }
  }
  dict.find(nameOfList)->second = list;
}

void nikiforova::doReplace(const std::string& nameOfList, long long value, const std::string& sourceList, DictOfLists& dict)
{
  nikiforova::DictOfLists::ConstIterator cIter = dict.find(sourceList);
  if (cIter == dict.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::BidirectionalList< long long > destList = dict.find(nameOfList)->second;
  nikiforova::BidirectionalList< long long >::Iterator destIter = destList.begin();
  while (destIter != destList.end())
  {
    if (*destIter == value)
    {
      destIter = destList.erase(destIter);
      nikiforova::BidirectionalList< long long >::Iterator sourceIter = dict.find(sourceList)->second.begin();
      while (sourceIter != dict.find(sourceList)->second.end())
      {
        destList.insert(*sourceIter, destIter);
        ++sourceIter;
      }
    }
    ++destIter;
  }
  dict.find(nameOfList)->second = destList;
}

void nikiforova::remove(std::string& str, DictOfLists& dict)
{
  int countArgs = 0;
  std::string nameOfList = nikiforova::getWord(str);
  if (!nameOfList.empty())
  {
    countArgs++;
  }
  std::string arg = "";
  if (!str.empty())
  {
    arg = nikiforova::getWord(str);
    countArgs++;
  }
  if (countArgs != 2)
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::DictOfLists::ConstIterator cIter = dict.find(nameOfList);
  if (cIter == dict.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  if (nikiforova::isNumber(arg))
  {
    nikiforova::doRemove(nameOfList, std::stoll(arg), dict);
  }
  else
  {
    cIter = dict.find(arg);
    if (cIter == dict.cend())
    {
      nikiforova::invalidCommandMessage(std::cout);
      return;
    }
    nikiforova::doRemove(nameOfList, arg, dict);
  }
}

void nikiforova::doRemove(const std::string& nameOfList, long long value, DictOfLists& dict)
{
  nikiforova::BidirectionalList< long long > destList = dict.find(nameOfList)->second;
  nikiforova::BidirectionalList< long long >::Iterator destIter = destList.begin();
  while (destIter != destList.end())
  {
    if (*destIter == value)
    {
      destIter = destList.erase(destIter);
    }
    if (destIter != destList.end())
    {
      ++destIter;
    }
  }
  dict.find(nameOfList)->second = destList;
}

void nikiforova::doRemove(const std::string& nameOfList, const std::string& nameOfSourceList, DictOfLists& dict)
{
  nikiforova::BidirectionalList< long long > destList = dict.find(nameOfList)->second;
  nikiforova::BidirectionalList< long long >::Iterator destIter = destList.begin();
  nikiforova::BidirectionalList< long long > sourceList = dict.find(nameOfSourceList)->second;
  nikiforova::BidirectionalList< long long >::Iterator sourceIter = sourceList.begin();
  while (sourceIter != sourceList.end())
  {
    destIter = destList.begin();
    while (destIter != destList.end())
    {
      if (*destIter == *sourceIter)
      {
        destIter = destList.erase(destIter);
      }
      if (destIter != destList.end())
      {
        ++destIter;
      }
    }
    ++sourceIter;
  }
  dict.find(nameOfList)->second = destList;
}

void nikiforova::concat(std::string& str, DictOfLists& dict)
{
  int countArgs = 0;
  std::string nameOfList = nikiforova::getWord(str);
  if (!nameOfList.empty())
  {
    countArgs++;
  }
  nikiforova::BidirectionalList< long long > newList;
  while (!str.empty())
  {
    std::string word = nikiforova::getWord(str);
    countArgs++;
    auto iter = dict.find(word);
    if (iter == dict.end())
    {
      nikiforova::invalidCommandMessage(std::cout);
      return;
    }
    BidirectionalList< long long > temp = dict.get(word);
    for (auto&& item: temp)
    {
      newList.pushBack(item);
    }
  }
  if (countArgs < 3)
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  dict.push(nameOfList, newList);
}

void nikiforova::equal(std::string& str, DictOfLists& dict)
{
  nikiforova::doEqual(std::cout, str, dict);
}

std::ostream& nikiforova::doEqual(std::ostream& out, std::string& str, DictOfLists& dict)
{
  int countArgs = 0;
  std::string word1 = nikiforova::getWord(str);
  if (!word1.empty())
  {
    countArgs++;
  }
  DictOfLists::ConstIterator cIter1 = dict.find(word1);
  if (cIter1 == dict.cend())
  {
    return nikiforova::invalidCommandMessage(out);
  }
  while (!str.empty())
  {
    std::string word2 = nikiforova::getWord(str);
    countArgs++;
    BidirectionalList< long long > list1 = dict.get(word1);
    DictOfLists::ConstIterator cIter2 = dict.find(word2);
    if (cIter2 == dict.cend())
    {
      return nikiforova::invalidCommandMessage(out);
    }
    BidirectionalList< long long > list2 = dict.get(word2);
    if (list1 != list2)
    {
      return out << "<FALSE>\n";
    }
    word1 = word2;
  }
  if (countArgs < 2)
  {
    return nikiforova::invalidCommandMessage(std::cout);
  }
  return out << "<TRUE>\n";
}
