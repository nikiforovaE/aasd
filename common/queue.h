#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

namespace nikiforova {
  template< typename T >
  class Queue {
  public:
    void push(const T&);
    void drop();
    const T& getFront() const;
    const T& getBack() const;
    bool isEmpty() const noexcept;
    size_t getLenght() const;
  private:
    nikiforova::detail::List< T > list_;
  };

  template< typename T >
  void Queue< T >::push(const T& x)
  {
    list_.pushBack(x);
  }

  template< typename T >
  void Queue< T >::drop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    list_.popFront();
  }

  template< typename T >
  const T& Queue< T >::getFront() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    return list_.getFront();
  }

  template< typename T >
  const T& Queue< T >::getBack() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    return list_.getBack();
  }

  template< typename T >
  bool Queue< T >::isEmpty() const noexcept
  {
    return list_.isEmpty();
  }

  template< typename T >
  inline size_t Queue< T >::getLenght() const
  {
    return list_.size();
  }
}
#endif
