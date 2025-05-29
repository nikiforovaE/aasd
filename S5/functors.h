#ifndef FUNCTORS_H
#define FUNCTORS_H
#include <utility>
#include <string>

namespace nikiforova {
  class Key_summ {
  public:
    Key_summ();
    void operator()(const std::pair< long long, std::string >& data);
    long long getKeySumm();
  private:
    long long keySumm_;
  };

  class Value_summ {
  public:
    Value_summ();
    void operator()(const std::pair< long long, std::string >& data);
    std::string getValueSumm();
  private:
    std::string valueSumm_;
  };

  class Key_value_summ {
  public:
    std::string getResultSumm();
    void operator()(const std::pair< long long, std::string >& data);
  private:
    Key_summ key_;
    Value_summ value_;
    std::string resultSumm;
  };

}
#endif
