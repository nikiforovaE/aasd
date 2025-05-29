#ifndef EXPRESSIONPART_H
#define EXPRESSIONPART_H
namespace nikiforova {

  enum class ExpressionType {
    OpenedBracket,
    ClosedBracket,
    Operand,
    Operation
  };

  class ExpressionPart {
  public:

    explicit ExpressionPart(char);
    explicit ExpressionPart(long long);
    ~ExpressionPart() = default;

    bool operator==(const ExpressionPart&) const;
    bool operator!=(const ExpressionPart&) const;

    ExpressionType getType() const;
    long long getOperand() const;
    char getOperation() const;
    char getBracket() const;

  private:
    ExpressionType type_;
    union {
      char mathSymbol_;
      long long operand_;
    };
  };
}
#endif
