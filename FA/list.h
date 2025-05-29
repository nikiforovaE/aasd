#ifndef LIST_H
#define LIST_H
#include <iostream>

namespace nikiforova {

  namespace detail {
    template< typename T >
    struct node_t
    {
      T data_;
      node_t* next_;
    };

    template< typename T >
    class List {
    public:
      List();
      List(const List&);
      List(List&&) noexcept;
      ~List();
      List& operator= (const List&);
      List& operator= (List&&) noexcept;
      size_t size() const noexcept;
      void pushFront(const T&);
      void popFront();
      void pushBack(const T&);
      void swap(List&) noexcept;
      void clear();
      bool isEmpty() const noexcept;
      const T& getFront() const;
      const T& getBack() const;

    protected:
      node_t< T >* head_;
      node_t< T >* tail_;
      size_t size_;
    };

    template< typename T >
    List< T >::List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    template< typename T >
    List< T >::List(const List< T >& x):
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      if (!x.isEmpty())
      {
        node_t< T >* srcPtr = x.head_;
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
    List< T >::List(List< T >&& rhs) noexcept:
      head_(rhs.head_),
      tail_(rhs.tail_),
      size_(rhs.size_)
    {
      rhs.tail_ = nullptr;
      rhs.head_ = nullptr;
      rhs.size_ = 0;
    }

    template< typename T >
    List< T >::~List()
    {
      clear();
    }

    template< typename T >
    List< T >& List< T >::operator=(const List< T >& x)
    {
      if (this != std::addressof(x))
      {
        List< T > temp(x);
        swap(temp);
      }
      return *this;
    }

    template< typename T >
    List< T >& List< T >::operator=(List< T >&& rhs) noexcept
    {
      if (this != std::addressof(rhs))
      {
        List< T > temp(std::move(rhs));
        swap(temp);
      }
      return *this;
    }

    template< typename T >
    size_t List< T >::size() const noexcept
    {
      return size_;
    }

    template< typename T >
    void List< T >::pushFront(const T& val)
    {
      head_ = new node_t< T >{ val, head_ };
      size_++;
    }

    template< typename T >
    void List< T >::popFront()
    {
      if (isEmpty())
      {
        throw std::logic_error("Empty list");
      }
      node_t< T >* newHead = head_->next_;
      if (head_ == tail_)
      {
        tail_ = nullptr;
      }
      delete head_;
      head_ = newHead;
      size_--;
    }

    template< typename T >
    void List< T >::pushBack(const T& val)
    {
      if (isEmpty())
      {
        head_ = new node_t< T >{ val, nullptr };
        tail_ = head_;
      }
      else
      {
        tail_->next_ = new node_t< T >{ val, nullptr };
        tail_ = tail_->next_;
      }
      size_++;
    }

    template< typename T >
    void List< T >::swap(List< T >& x) noexcept
    {
      std::swap(head_, x.head_);
      std::swap(tail_, x.tail_);
      std::swap(size_, x.size_);
    }

    template< typename T >
    void List< T >::clear()
    {
      while (!isEmpty())
      {
        popFront();
      }
    }

    template< typename T >
    bool List< T >::isEmpty() const noexcept
    {
      return !size_;
    }

    template< typename T >
    const T& List< T >::getFront() const
    {
      if (isEmpty())
      {
        throw std::logic_error("Empty list");
      }
      return head_->data_;
    }

    template< typename T >
    const T& List< T >::getBack() const
    {
      if (isEmpty())
      {
        throw std::logic_error("Empty list");
      }
      return tail_->data_;
    }
  }
}
#endif
