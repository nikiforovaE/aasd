#include "errorMessages.h"

std::ostream& nikiforova::invalidCommandMessage(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
}
std::ostream& nikiforova::emptyMessage(std::ostream& out)
{
  return out << "<EMPTY>\n";
}
