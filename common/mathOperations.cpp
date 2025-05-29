#include "mathOperations.h"
#include <limits>
#include <stdexcept>

long long nikiforova::sum(long long a, long long b)
{
  const long long max = std::numeric_limits< long long >::max();
  const long long min = std::numeric_limits< long long >::min();
  long long result = 0;
  if (a > 0 && b > 0)
  {
    if (max - a < b)
    {
      throw std::overflow_error("Overflow");
    }
    else
    {
      result = a + b;
    }
  }
  else if (a < 0 && b < 0)
  {
    if (min - a > b)
    {
      throw std::underflow_error("Underflow");
    }
    else
    {
      result = a + b;
    }
  }
  else
  {
    result = a + b;
  }
  return result;
}

long long nikiforova::mult(long long a, long long b)
{
  long long result = 0;
  if ((a > 0 && b > 0) || (a < 0 && b < 0))
  {
    const long long max = std::numeric_limits< long long >::max();
    if (max / a < b)
    {
      throw std::overflow_error("Overflow");
    }
    else
    {
      result = a * b;
    }
  }
  else
  {
    const long long min = std::numeric_limits< long long >::min();
    if (b < min / a)
    {
      throw std::underflow_error("Underflow");
    }
    else
    {
      result = a * b;
    }
  }
  return result;
}

long long nikiforova::mod(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("Division by 0");
  }
  if ((a > 0 && b > 0) || (a < 0 && b < 0))
  {
    return a % b;
  }
  else
  {
    return ((a % b + b) % b);
  }
}
