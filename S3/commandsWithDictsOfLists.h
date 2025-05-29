#ifndef COMMANDSWITHDICTSOFLISTS_H
#define COMMANDSWITHDICTSOFLISTS_H
#include "dictionary.h"
#include "bidirectionalList.h"

namespace nikiforova {
  using DictOfLists = Dictionary< std::string, BidirectionalList< long long > >;

  DictOfLists readAllLists(std::istream&);
  BidirectionalList< long long > convertStringToList(std::string&);
  void print(std::string&, DictOfLists&);
  void replace(std::string&, DictOfLists&);
  void remove(std::string&, DictOfLists&);
  void concat(std::string&, DictOfLists&);
  void equal(std::string&, DictOfLists&);

  std::ostream& doPrint(std::ostream&, std::string&, DictOfLists);
  void doReplace(const std::string&, long long, long long, DictOfLists&);
  void doReplace(const std::string&, long long, const std::string&, DictOfLists&);
  void doRemove(const std::string&, long long, DictOfLists&);
  void doRemove(const std::string&, const std::string&, DictOfLists&);
  std::ostream& doEqual(std::ostream&, std::string&, DictOfLists&);
}
#endif

