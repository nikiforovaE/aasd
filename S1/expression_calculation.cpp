#include "expression_calculation.h"
#include <string>
#include <limits>
#include "expressionPart.h"
#include "stack.h"
#include "queue.h"
#include "mathOperations.h"

namespace {
  bool isSecondHasPriority(nikiforova::ExpressionPart ob1, nikiforova::ExpressionPart ob2)
  {
    using nikiforova::ExpressionPart;
    bool a = (ob1 == ExpressionPart('+') || ob1 == ExpressionPart('-'));
    bool b = ob2 == ExpressionPart('*') || ob2 == ExpressionPart('/') || ob2 == ExpressionPart('%');
    return a && b;
  }
   nikiforova::Queue< nikiforova::ExpressionPart > convertStringToInfix(std::string& str)
  {
    {
      nikiforova::Queue< nikiforova::ExpressionPart > inputQueue;
      for (unsigned int i = 0; i < str.length(); i++)
      {
        if (std::isspace(str[i]))
        {
          continue;
        }
        if (std::isalpha(str[i]))
        {
          throw std::logic_error("Incorrect expression");
        }
        if (str[i] == '(' || str[i] == ')' || (nikiforova::isMathOperation(str[i]) && std::isspace(str[i + 1])))
        {
          inputQueue.push(nikiforova::ExpressionPart(str[i]));
        }
        else
        {
          std::string temp = "";
          if (str[i] == '-')
          {
            temp.push_back(str[i]);
            i++;
          }
          while (isdigit(str[i]))
          {
            temp.push_back(str[i]);
            i++;
          }
          inputQueue.push(nikiforova::ExpressionPart(std::stoll(temp)));
        }
      }
      return inputQueue;
    }
  }

  nikiforova::Queue< nikiforova::ExpressionPart > convertInfixToPostfix(nikiforova::Queue< nikiforova::ExpressionPart > infixQueue)
  {
    nikiforova::Queue< nikiforova::ExpressionPart > postixQueue;
    nikiforova::Stack< nikiforova::ExpressionPart > stack;
    using nikiforova::ExpressionType;
    using nikiforova::ExpressionPart;
    long long countOpenBrackets = 0;
    long long countClosedBrackets = 0;
    long long countOperations = 0;
    long long countOperands = 0;
    while (!infixQueue.isEmpty())
    {
      if (infixQueue.getFront() == ExpressionPart('('))
      {
        stack.push(infixQueue.getFront());
        infixQueue.drop();
        countOpenBrackets++;
      }
      else if (infixQueue.getFront() == ExpressionPart(')'))
      {
        countClosedBrackets++;
        if (countClosedBrackets > countOpenBrackets)
        {
          throw std::logic_error("Incorrect expression");
        }
        while (stack.getTop() != ExpressionPart('('))
        {
          postixQueue.push(stack.getTop());
          stack.getTop().getType() == ExpressionType::Operation ? countOperations++ : countOperands++;
          stack.drop();
        }
        stack.drop();
        infixQueue.drop();
      }
      else if (infixQueue.getFront().getType() == ExpressionType::Operand)
      {
        postixQueue.push(infixQueue.getFront());
        infixQueue.drop();
        countOperands++;
      }
      else
      {
        bool isInfixOperation = infixQueue.getFront().getType() == ExpressionType::Operation;
        bool isStackOperation = !stack.isEmpty() ? stack.getTop().getType() == ExpressionType::Operation : 0;
        while (!stack.isEmpty() && isInfixOperation && isStackOperation && (!isSecondHasPriority(infixQueue.getFront(), stack.getTop())))
        {
          postixQueue.push(stack.getTop());
          countOperations++;
          stack.drop();
          stack.push(infixQueue.getFront());
          infixQueue.drop();
          isInfixOperation = infixQueue.getFront().getType() == ExpressionType::Operation;
          isStackOperation = stack.getTop().getType() == ExpressionType::Operation;
        }
        stack.push(infixQueue.getFront());
        infixQueue.drop();
      }
    }
    while (!stack.isEmpty())
    {
      postixQueue.push(stack.getTop());
      stack.getTop().getType() == ExpressionType::Operation ? countOperations++ : countOperands++;
      stack.drop();
    }
    if ((countClosedBrackets != countOpenBrackets) || (countOperands - countOperations != 1))
    {
      throw std::logic_error("Incorrect expression");
    }
    return postixQueue;
  }
}


bool nikiforova::isMathOperation(char s)
{
  return s == '+' || s == '-' || s == '*' || s == '/' || s == '%';
}

long long nikiforova::calculate(std::string& str)
{
  nikiforova::Queue< nikiforova::ExpressionPart > inputQueue;
  inputQueue = ::convertStringToInfix(str);
  nikiforova::Queue< nikiforova::ExpressionPart > postfixQueue;
  postfixQueue = ::convertInfixToPostfix(inputQueue);
  nikiforova::Stack< ExpressionPart > stack;
  long long result = 0;
  while (!postfixQueue.isEmpty())
  {
    if (postfixQueue.getFront().getType() == ExpressionType::Operand)
    {
      stack.push(postfixQueue.getFront());
      postfixQueue.drop();
    }
    else if (postfixQueue.getFront().getType() == ExpressionType::Operation)
    {
      char operation = postfixQueue.getFront().getOperation();
      postfixQueue.drop();
      long long a = stack.getTop().getOperand();
      stack.drop();
      long long b = stack.getTop().getOperand();
      stack.drop();
      if (operation == '+')
      {
        result = nikiforova::sum(a, b);
      }
      else if (operation == '-')
      {
        result = nikiforova::sum(a * (-1), b);
      }
      else if (operation == '*')
      {
        result = nikiforova::mult(a, b);
      }
      else if (operation == '/')
      {
        if (a == 0)
        {
          throw std::logic_error("Division by 0");
        }
        result = b / a;
      }
      else
      {
        result = nikiforova::mod(b, a);
      }
      stack.push(ExpressionPart(result));
    }
  }
  if (!stack.isEmpty() && stack.getTop().getType() == ExpressionType::Operand)
  {
    result = stack.getTop().getOperand();
  }
  return result;
}
