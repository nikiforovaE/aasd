#ifndef BIDIRECTIONALLIST_H
#define BIDIRECTIONALLIST_H
#include <cassert>
#include <stdexcept>
#include <iterator>
#include <cstddef>
#include <utility>

namespace nikiforova {

  namespace detail {
    template< typename T >
    struct biNode_t {
      T data_;
      biNode_t* prev_;
      biNode_t* next_;
    };
  }

  template< typename T >
  class BidirectionalList {
  public:
    BidirectionalList();
    BidirectionalList(const BidirectionalList&);
    BidirectionalList(BidirectionalList&&) noexcept;
    ~BidirectionalList();

    BidirectionalList& operator= (const BidirectionalList&);
    BidirectionalList& operator= (BidirectionalList&&) noexcept;
    bool operator==(BidirectionalList&);
    bool operator!=(BidirectionalList&);

    size_t size() const noexcept;
    void pushFront(const T&);
    void popFront();
    void pushBack(const T&);
    void popBack();
    void swap(BidirectionalList&) noexcept;
    void clear();
    bool isEmpty() const noexcept;
    const T& getFront() const;
    const T& getBack() const;

    class Iterator: public std::iterator< std::bidirectional_iterator_tag, T > {
    public:
      friend class BidirectionalList< T >;
      Iterator():
        node_(nullptr)
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
      Iterator& operator--()
      {
        assert(node_ != nullptr);
        node_ = node_->prev_;
        return *this;
      }
      Iterator operator--(int)
      {
        assert(node_ != nullptr);
        Iterator result(*this);
        --(*this);
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
      detail::biNode_t< T >* node_;
      Iterator(detail::biNode_t< T >* rhsNode):
        node_(rhsNode)
      {}
    };

    class ConstIterator: public std::iterator< std::bidirectional_iterator_tag, T > {
    public:
      friend class BidirectionalList< T >;
      ConstIterator():
        node_(nullptr)
      {}
      ~ConstIterator() = default;
      ConstIterator(const ConstIterator&) = default;
      ConstIterator& operator=(const ConstIterator&) = default;
      ConstIterator& operator++()
      {
        assert(node_ != nullptr);
        node_ = node_->next_;
        return *this;
      }
      ConstIterator operator++(int)
      {
        assert(node_ != nullptr);
        ConstIterator result(*this);
        ++(*this);
        return result;
      }
      ConstIterator& operator--()
      {
        assert(node_ != nullptr);
        node_ = node_->prev_;
        return *this;
      }
      ConstIterator operator--(int)
      {
        assert(node_ != nullptr);
        ConstIterator result(*this);
        --(*this);
        return result;
      }
      const T& operator*()
      {
        assert(node_ != nullptr);
        return node_->data_;
      }
      const T* operator->()
      {
        assert(node_ != nullptr);
        return std::addressof(node_->data_);
      }
      bool operator==(const ConstIterator& rhs) const
      {
        return node_ == rhs.node_;
      }
      bool operator!=(const ConstIterator& rhs) const
      {
        return !(rhs == *this);
      }
    private:
      const detail::biNode_t< T >* node_;
    };

    Iterator insert(const T&, Iterator);
    Iterator erase(Iterator);
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

  private:
    detail::biNode_t< T >* head_;
    detail::biNode_t< T >* tail_;
    size_t size_;
  };

  template< typename T >
  BidirectionalList< T >::BidirectionalList():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  BidirectionalList< T >::BidirectionalList(const BidirectionalList& x):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    if (!x.isEmpty())
    {
      detail::biNode_t< T >* srcPtr = x.head_;
      try
      {
        while (srcPtr)
        {
          pushBack(srcPtr->data_);
          srcPtr = srcPtr->next_;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  }

  template< typename T >
  BidirectionalList< T  >::BidirectionalList(BidirectionalList&& rhs) noexcept:
    head_(rhs.head_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename T >
  BidirectionalList< T >::~BidirectionalList()
  {
    clear();
  }

  template< typename T >
  BidirectionalList< T >& BidirectionalList< T >::operator=(const BidirectionalList< T >& rhs)
  {
    if (this != std::addressof(rhs))
    {
      BidirectionalList< T > temp(rhs);
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  BidirectionalList< T >& BidirectionalList< T >::operator=(BidirectionalList< T >&& rhs) noexcept
  {
    if (this != std::addressof(rhs))
    {
      BidirectionalList< T > temp(std::move(rhs));
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  bool BidirectionalList< T >::operator==(BidirectionalList& rhs)
  {
    BidirectionalList< long long >::Iterator lhsIter = begin();
    BidirectionalList< long long >::Iterator rhsIter = rhs.begin();
    if (size_ != rhs.size_)
    {
      return false;
    }
    while (lhsIter != end())
    {
      if (*lhsIter != *rhsIter)
      {
        return false;
      }
      ++lhsIter;
      ++rhsIter;
    }
    return true;
  }

  template< typename T >
  bool BidirectionalList< T >::operator!=(BidirectionalList& rhs)
  {
    return !(*this == rhs);
  }

  template< typename T >
  size_t BidirectionalList< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void BidirectionalList< T >::pushFront(const T& val)
  {
    detail::biNode_t< T >* temp = new detail::biNode_t< T >{ val, nullptr, head_ };
    if (!isEmpty())
    {
      head_->prev_ = temp;
    }
    else
    {
      tail_ = temp;
    }
    head_ = temp;
    size_++;
  }

  template< typename T >
  void BidirectionalList< T >::popFront()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty list");
    }
    detail::biNode_t< T >* newHead = head_->next_;
    if (head_ == tail_)
    {
      tail_ = nullptr;
    }
    delete head_;
    if (newHead != nullptr)
    {
      newHead->prev_ = nullptr;
    }
    head_ = newHead;
    size_--;
  }

  template< typename T >
  void BidirectionalList< T >::pushBack(const T& val)
  {
    if (isEmpty())
    {
      head_ = new detail::biNode_t< T >{ val, nullptr, nullptr };
      tail_ = head_;
    }
    else
    {
      tail_->next_ = new detail::biNode_t< T >{ val, tail_, nullptr };
      tail_ = tail_->next_;
    }
    size_++;
  }

  template< typename T >
  void BidirectionalList< T >::popBack()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty list");
    }
    detail::biNode_t< T >* newTail = tail_->prev_;
    tail_->prev_->next_ = nullptr;
    delete tail_;
    tail_ = newTail;
    size_--;
  }

  template< typename T >
  void BidirectionalList< T >::swap(BidirectionalList& rhs) noexcept
  {
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    std::swap(size_, rhs.size_);
  }

  template< typename T >
  void BidirectionalList< T >::clear()
  {
    while (!isEmpty())
    {
      popFront();
    }
  }

  template< typename T >
  bool BidirectionalList< T >::isEmpty() const noexcept
  {
    return !size_;
  }

  template< typename T >
  const T& BidirectionalList< T >::getFront() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty list");
    }
    return head_->data_;
  }

  template< typename T >
  const T& BidirectionalList< T >::getBack() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty list");
    }
    return tail_->data_;
  }

  template< typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::insert(const T& data, Iterator iter)
  {
    if (iter == begin())
    {
      pushFront(data);
      return iter;
    }
    if (iter == end())
    {
      pushBack(data);
      return iter;
    }
    else
    {
      Iterator temp = begin();
      detail::biNode_t< T >* tempNode = head_;
      while (++temp != iter)
      {
        tempNode = tempNode->next_;
      }
      tempNode->next_ = new detail::biNode_t< T >{ data, tempNode, tempNode->next_ };
      tempNode->next_->next_->prev_ = tempNode->next_;
      size_++;
      return tempNode->next_;
    }
  }

  template < typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::erase(Iterator iter)
  {
    if (iter == begin())
    {
      popFront();
      return begin();
    }
    if (iter == end())
    {
      throw std::logic_error("Can't erase");
    }
    if (++iter == end())
    {
      popBack();
      return end();
    }
    Iterator tempIter = begin();
    detail::biNode_t< T >* tempNode = head_;
    while (++tempIter != iter)
    {
      tempNode = tempNode->next_;
    }
    detail::biNode_t< T >* tempTempNode = tempNode->next_;
    tempTempNode->prev_ = tempNode->prev_;
    tempNode->prev_->next_ = tempTempNode;
    delete tempNode;
    size_--;
    return tempTempNode;
  }

  template< typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::begin() noexcept
  {
    return Iterator(head_);
  }

  template< typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::end() noexcept
  {
    return Iterator(nullptr);
  }

  template< typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::cbegin() const noexcept
  {
    return ConstIterator(head_);
  }

  template< typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::cend() const noexcept
  {
    return ConstIterator(nullptr);
  }
}
#endif
