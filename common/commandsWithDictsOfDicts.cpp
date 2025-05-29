#include "commandsWithDictsOfDicts.h"
#include <string>
#include <iostream>
#include "2-3Tree.h"
#include "forwardList.h"
#include "errorMessages.h"
#include "operationsWithStrings.h"

nikiforova::DictOfDicts nikiforova::readAllDictsFromStream(std::istream& in)
{
  nikiforova::DictOfDicts result;
  while (!in.eof())
  {
    std::string str = "";
    std::getline(in, str);
    std::string nameOfDict = nikiforova::getWord(str);
    nikiforova::DictOfDicts::ConstIterator cIter = result.cfind(nameOfDict);
    if (cIter != result.cend())
    {
      throw std::logic_error("Dictionary with the same name already exists");
    }
    else
    {
      nikiforova::Dict temp = nikiforova::convertStringToDict(str);
      result.push(nameOfDict, temp);
    }
  }
  return result;
}

nikiforova::Dict nikiforova::convertStringToDict(std::string& str)
{
  nikiforova::Dict dict;
  while (!str.empty())
  {
    long long key = 0;
    std::string value = "";
    std::string temp = "";
    if (str[0] == ' ')
    {
      str.erase(0, 1);
    }
    temp = str.substr(0, str.find(" ", 1));
    if (!nikiforova::isNumber(temp))
    {
      throw std::logic_error("Key is not a number");
    }
    key = std::stoll(temp);
    str = str.erase(0, temp.length() + 1);
    value = str.substr(0, str.find(" ", 1));
    str = str.erase(0, value.length() + 1);
    dict.push(key, value);
  }
  return dict;
}

std::ostream& nikiforova::doPrint(std::ostream& out, const std::string& dataset, const Dict& dict)
{
  if (dict.isEmpty())
  {
    return nikiforova::emptyMessage(out);
  }
  out << dataset;
  for (auto&& pair: dict)
  {
    out << " " << pair.first << " " << pair.second;
  }
  out << "\n";
  return out;
}

void nikiforova::print(std::string& str, DictOfDicts& dicts)
{
  std::string nameOfDict = nikiforova::getWord(str);
  nikiforova::DictOfDicts::ConstIterator cIter = dicts.cfind(nameOfDict);
  if (cIter == dicts.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::Dict dict = cIter->second;
  nikiforova::doPrint(std::cout, nameOfDict, dict);
}

void nikiforova::doComplement(const std::string& newDataset, const std::string& dataset1, const std::string& dataset2, DictOfDicts& dict)
{
  nikiforova::DictOfDicts::ConstIterator cIter1 = dict.cfind(dataset1);
  nikiforova::DictOfDicts::ConstIterator cIter2 = dict.cfind(dataset2);
  if ((cIter1 == dict.cend()) || cIter2 == dict.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::Dict result = Dict(cIter1->second);
  auto listIter = cIter2->second.cbegin();
  while (listIter != cIter2->second.cend())
  {
    auto key = listIter->first;
    if (result.find(key) != result.end())
    {
      result.drop(key);
    }
    listIter++;
  }
  if (dict.find(newDataset) != dict.end())
  {
    dict.drop(newDataset);
  }
  dict.push(newDataset, result);
}
void nikiforova::complement(std::string& str, DictOfDicts& dict)
{
  std::string newDataset = nikiforova::getWord(str);
  std::string dataset1 = nikiforova::getWord(str);
  std::string dataset2 = nikiforova::getWord(str);
  nikiforova::doComplement(newDataset, dataset1, dataset2, dict);
}

void nikiforova::doIntersect(const std::string& newDataset, const std::string& dataset1, const std::string& dataset2, DictOfDicts& dict)
{
  nikiforova::DictOfDicts::ConstIterator cIter1 = dict.cfind(dataset1);
  nikiforova::DictOfDicts::ConstIterator cIter2 = dict.cfind(dataset2);
  if ((cIter1 == dict.cend()) || cIter2 == dict.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::Dict result;
  auto listIter1 = cIter1->second.cbegin();
  while (listIter1 != cIter1->second.cend())
  {
    auto key1 = listIter1->first;
    auto listIter2 = cIter2->second.cbegin();
    while (listIter2 != cIter2->second.cend())
    {
      auto key2 = listIter2->first;
      if ((key1 == key2) && (result.find(key1) == result.end()))
      {
        result.push(key1, listIter1->second);
      }
      listIter2++;
    }
    listIter1++;
  }
  if (dict.find(newDataset) != dict.end())
  {
    dict.drop(newDataset);
  }
  dict.push(newDataset, result);
}
void nikiforova::intersect(std::string& str, DictOfDicts& dict)
{
  std::string newDataset = nikiforova::getWord(str);
  std::string dataset1 = nikiforova::getWord(str);
  std::string dataset2 = nikiforova::getWord(str);
  nikiforova::doIntersect(newDataset, dataset1, dataset2, dict);
}
void nikiforova::doUnion(const std::string& newDataset, const std::string& dataset1, const std::string& dataset2, DictOfDicts& dict)
{
  nikiforova::DictOfDicts::ConstIterator cIter1 = dict.cfind(dataset1);
  nikiforova::DictOfDicts::ConstIterator cIter2 = dict.cfind(dataset2);
  if ((cIter1 == dict.cend()) || cIter2 == dict.cend())
  {
    nikiforova::invalidCommandMessage(std::cout);
    return;
  }
  nikiforova::Dict result = Dict(dict.get(dataset1));
  auto listIter = cIter2->second.cbegin();
  while (listIter != cIter2->second.cend())
  {
    auto key = listIter->first;
    if (result.find(key) == result.end())
    {
      result.push(key, listIter->second);
    }
    listIter++;
  }
  if (dict.find(newDataset) != dict.end())
  {
    dict.drop(newDataset);
  }
  dict.push(newDataset, result);
}
void nikiforova::myUnion(std::string& str, DictOfDicts& dict)
{
  std::string newDataset = nikiforova::getWord(str);
  std::string dataset1 = nikiforova::getWord(str);
  std::string dataset2 = nikiforova::getWord(str);
  nikiforova::doUnion(newDataset, dataset1, dataset2, dict);
}
