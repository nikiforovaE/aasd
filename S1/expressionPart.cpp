#include <stdexcept>
#include "expressionPart.h"
#include "expression_calculation.h"

nikiforova::ExpressionPart::ExpressionPart(char s)
{
  if (s == '(')
  {
    type_ = ExpressionType::OpenedBracket;
    mathSymbol_ = s;
  }
  else if (s == ')')
  {
    type_ = ExpressionType::ClosedBracket;
    mathSymbol_ = s;
  }
  else if (nikiforova::isMathOperation(s))
  {
    type_ = ExpressionType::Operation;
    mathSymbol_ = s;
  }
  else
  {
    throw std::logic_error("Not a bracket or math operation");
  }
}

nikiforova::ExpressionPart::ExpressionPart(long long x):
  type_(ExpressionType::Operand),
  operand_(x)
{}

bool nikiforova::ExpressionPart::operator==(const ExpressionPart& rhs) const
{
  return (type_ == rhs.type_) && (type_ == ExpressionType::Operand ? operand_ == rhs.operand_ : mathSymbol_ == rhs.mathSymbol_);
}

bool nikiforova::ExpressionPart::operator!=(const ExpressionPart& rhs) const
{
  return !(*this == rhs);
}

nikiforova::ExpressionType nikiforova::ExpressionPart::getType() const
{
  return type_;
}

long long nikiforova::ExpressionPart::getOperand() const
{
  if (type_ != ExpressionType::Operand)
  {
    throw std::logic_error("Not an operand");
  }
  return operand_;
}

char nikiforova::ExpressionPart::getOperation() const
{
  if (type_ != ExpressionType::Operation)
  {
    throw std::logic_error("Not an operation");
  }
  return mathSymbol_;
}

char nikiforova::ExpressionPart::getBracket() const
{
  if ((type_ != ExpressionType::OpenedBracket) || (type_ != ExpressionType::ClosedBracket))
  {
    throw std::logic_error("Not a bracket");
  }
  return mathSymbol_;
}
