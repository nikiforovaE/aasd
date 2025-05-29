#include "functors.h"
#include <string>
#include <iostream>
#include "mathOperations.h"

namespace nikiforova {
  Key_summ::Key_summ():
    keySumm_(0)
  {}

  void Key_summ::operator()(const std::pair< long long, std::string >& data)
  {
    keySumm_ = nikiforova::sum(keySumm_, data.first);
  }

  long long Key_summ::getKeySumm()
  {
    return keySumm_;
  }

  Value_summ::Value_summ():
    valueSumm_("")
  {}

  void Value_summ::operator()(const std::pair< long long, std::string >& data)
  {
    if (!valueSumm_.empty())
    {
      valueSumm_ += " ";
    }
    valueSumm_ += data.second;
  }

  std::string Value_summ::getValueSumm()
  {
    return valueSumm_;
  }

  std::string Key_value_summ::getResultSumm()
  {
    return std::to_string(key_.getKeySumm()) + " " + value_.getValueSumm();
  }

  void Key_value_summ::operator()(const std::pair< long long, std::string >& data)
  {
    key_(data);
    value_(data);
  }
}
