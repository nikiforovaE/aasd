#ifndef COMMANDSWITHDICTSOFDICTS_H
#define COMMANDSWITHDICTSOFDICTS_H
#include "2-3Tree.h"
namespace nikiforova {
  using Dict = Tree< long long, std::string >;
  using DictOfDicts = Tree< std::string, Dict >;

  DictOfDicts readAllDictsFromStream(std::istream&);
  Dict convertStringToDict(std::string&);

  std::ostream& doPrint(std::ostream&, const std::string&, const Dict&);
  void doComplement(const std::string&, const std::string&, const std::string&, DictOfDicts&);
  void doIntersect(const std::string&, const std::string&, const std::string&, DictOfDicts&);
  void doUnion(const std::string&, const std::string&, const std::string&, DictOfDicts&);

  void print(std::string&, DictOfDicts&);
  void complement(std::string&, DictOfDicts&);
  void intersect(std::string&, DictOfDicts&);
  void myUnion(std::string&, DictOfDicts&);

}
#endif
