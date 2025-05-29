#ifndef STACK_H
#define STACK_H
#include "list.h"

namespace nikiforova {
  template< typename T >
  class Stack {
  public:
    const T& getTop() const;
    void push(const T&);
    void drop();
    bool isEmpty() const noexcept;
    size_t getSize() const;
  private:
    nikiforova::detail::List< T > list_;
  };

  template< typename T >
  const T& Stack< T >::getTop() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    return list_.getFront();
  }

  template< typename T >
  void Stack< T >::push(const T& rhs)
  {
    list_.pushFront(rhs);
  }

  template< typename T >
  void Stack< T >::drop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    list_.popFront();
  }

  template< typename T >
  bool Stack< T >::isEmpty() const noexcept
  {
    return list_.isEmpty();
  }

  template< typename T >
  inline size_t Stack< T >::getSize() const
  {
    return list_.size();
  }
}
#endif
