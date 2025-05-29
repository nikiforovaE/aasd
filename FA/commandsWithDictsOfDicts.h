#ifndef COMMANDSWITHDICTSOFDICTS_H
#define COMMANDSWITHDICTSOFDICTS_H
#include "2-3Tree.h"
#include "2-3Set.h"

namespace nikiforova {
  using Dict = TreeSet< std::string >;
  using DictOfDicts = Tree< std::string, Dict >;

  DictOfDicts readAllDictsFromStream(std::istream&);
  Dict convertStringToDict(std::string&);

  std::ostream& doPrint(std::ostream&, const std::string&, const Dict&);
  std::ostream& getWordsWithPrefix(std::ostream&, const std::string&, const Dict&);
  void doComplement(const std::string&, const std::string&, const std::string&, DictOfDicts&);
  void doIntersect(const std::string&, const std::string&, const std::string&, DictOfDicts&);
  void doUnion(const std::string&, const std::string&, const std::string&, DictOfDicts&);
  std::ostream& isContain(std::ostream&, const std::string&, const Dict&);
  void doSave(const std::string&, const std::string&, const Dict&);

  void print(std::string&, const DictOfDicts&);
  void complement(std::string&, DictOfDicts&);
  void intersect(std::string&, DictOfDicts&);
  void myUnion(std::string&, DictOfDicts&);
  void wordsWithPrefix(std::string&, const DictOfDicts&);
  void contain(std::string&, const DictOfDicts&);
  void save(std::string&, const DictOfDicts&);

}
#endif
