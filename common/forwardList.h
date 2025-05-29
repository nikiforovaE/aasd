#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <cassert>
#include <stdexcept>
#include "list.h"

namespace nikiforova {
  template< typename T >
  class ForwardList: public nikiforova::detail::List< T > {
  public:
    ForwardList();
    ForwardList(const ForwardList&);
    ForwardList(ForwardList&&) noexcept;
    ~ForwardList();
    size_t size() const noexcept;
    void pushFront(const T&);
    void popFront();
    void pushBack(const T&);
    void swap(ForwardList&) noexcept;
    void clear();
    bool isEmpty() const noexcept;
    const T& getFront() const;
    const T& getBack() const;

    class Iterator {
    public:
      friend class ForwardList< T >;
      Iterator():
        node_(nullptr)
      {}
      Iterator(detail::node_t< T >* rhsNode):
        node_(rhsNode)
      {}
      ~Iterator() = default;
      Iterator(const Iterator&) = default;
      Iterator& operator=(const Iterator&) = default;
      Iterator& operator++()
      {
        assert(node_ != nullptr);
        node_ = node_->next_;
        return *this;
      }
      Iterator operator++(int)
      {
        assert(node_ != nullptr);
        Iterator result(*this);
        ++(*this);
        return result;
      }
      T& operator*()
      {
        assert(node_ != nullptr);
        return node_->data_;
      }
      T* operator->()
      {
        assert(node_ != nullptr);
        return std::addressof(node_->data_);
      }
      const T& operator*() const
      {
        assert(node_ != nullptr);
        return node_->data_;
      }
      const T* operator->() const
      {
        assert(node_ != nullptr);
        return std::addressof(node_->data_);
      }
      bool operator==(const Iterator& rhs) const
      {
        return node_ == rhs.node_;
      }
      bool operator!=(const Iterator& rhs) const
      {
        return !(rhs == *this);
      }
    private:
      detail::node_t< T >* node_;
    };

    class ConstIterator {
    public:
      friend class ForwardList< T >;
      ConstIterator():
        iterator_(nullptr)
      {}
      ConstIterator(Iterator iter):
        iterator_(iter)
      {}
      ~ConstIterator() = default;
      ConstIterator(const ConstIterator&) = default;
      ConstIterator& operator=(const ConstIterator&) = default;
      ConstIterator& operator++()
      {
        ++iterator_;
        return *this;
      }
      ConstIterator operator++(int)
      {
        return ConstIterator(iterator_++);
      }
      const T& operator*()
      {
        return *iterator_;
      }
      const T* operator->()
      {
        return std::addressof(*iterator_);
      }
      bool operator==(const ConstIterator& rhs) const
      {
        return iterator_ == rhs.iterator_;
      }
      bool operator!=(const ConstIterator& rhs) const
      {
        return !(rhs == *this);
      }
    private:
      Iterator iterator_;
    };

    void insert(const T&, ConstIterator);
    void erase(ConstIterator);
    Iterator begin() noexcept
    {
      return Iterator(detail::List< T >::head_);
    }
    Iterator end() noexcept
    {
      return Iterator(nullptr);
    }
    ConstIterator cbegin() const noexcept
    {
      return ConstIterator(detail::List< T >::head_);
    }
    ConstIterator cend() const noexcept
    {
      return ConstIterator(nullptr);
    }
  };

  template< typename T >
  void ForwardList< T >::insert(const T& data, ConstIterator iter)
  {
    if (iter == this->begin())
    {
      pushFront(data);
    }
    else
    {
      ConstIterator temp = this->cbegin();
      detail::node_t< T >* tempNode = detail::List< T >::head_;
      while (++temp != iter)
      {
        tempNode = tempNode->next_;
      }
      if (tempNode->next_ == nullptr)
      {
        tempNode->next_ = new detail::node_t< T >{ data, tempNode->next_ };
        detail::List< T >::tail_ = tempNode->next_;
      }
      else
      {
        tempNode->next_ = new detail::node_t< T >{ data, tempNode->next_ };
      }
      detail::List< T >::size_++;
    }
  }

  template< typename T >
  void ForwardList< T >::erase(ConstIterator iter)
  {
    ConstIterator tempIter = this->cbegin();
    detail::node_t< T >* tempNode = detail::List< T >::head_;
    if (tempIter == iter)
    {
      tempNode = tempNode->next_;
    }
    else
    {
      while (++tempIter != iter)
      {
        tempNode = tempNode->next_;
      }
    }
    if (tempIter == this->cbegin())
    {
      popFront();
    }
    else
    {
      detail::node_t< T >* tempTempNode = tempNode->next_->next_;
      delete tempNode->next_;
      tempNode->next_ = tempTempNode;
      if (tempTempNode == nullptr)
      {
        detail::List< T >::tail_ = tempNode;
      }
      detail::List< T >::size_--;
    }
  }

  template< typename T >
  ForwardList< T >::ForwardList():
    detail::List< T >::List()
  {}

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T >& x):
    detail::List< T >::List(x)
  {}

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T >&& rhs) noexcept:
    detail::List< T >::List(rhs)
  {}

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template< typename T >
  size_t ForwardList< T >::size() const noexcept
  {
    return detail::List< T >::size();
  }

  template< typename T >
  void ForwardList< T >::pushFront(const T& val)
  {
    detail::List< T >::pushFront(val);
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {
    detail::List< T >::popFront();
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T >& x) noexcept
  {
    detail::List< T >::swap(x);
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    detail::List< T >::clear();
  }

  template< typename T >
  void ForwardList< T >::pushBack(const T& val)
  {
    detail::List< T >::pushBack(val);
  }

  template< typename T >
  bool ForwardList< T >::isEmpty() const noexcept
  {
    return detail::List< T >::isEmpty();
  }

  template< typename T >
  const T& ForwardList< T >::getFront() const
  {
    return detail::List< T >::getFront();
  }

  template< typename T >
  const T& ForwardList< T >::getBack() const
  {
    return detail::List< T >::getBack();
  }
}
#endif
