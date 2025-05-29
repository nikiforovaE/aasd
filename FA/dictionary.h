#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <utility>
#include "forwardList.h"
namespace nikiforova {
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary {
  public:
    using Iterator = typename ForwardList< std::pair< Key, Value > >::Iterator;
    using ConstIterator = typename ForwardList< std::pair< Key, Value > >::ConstIterator;
    using pairIterBool = std::pair< typename Dictionary< Key, Value, Compare >::Iterator, bool >;
    Dictionary() = default;
    Dictionary(std::initializer_list< std::pair< Key, Value > >);
    Dictionary(const Dictionary&) = default;
    Dictionary(Dictionary&&) = default;
    ~Dictionary() = default;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void push(const Key& k, const Value& v);
    Iterator find(const Key& k);
    ConstIterator find(const Key& k) const;
    Value get(const Key& k);
    void drop(Key k);
    pairIterBool insert(const std::pair< Key, Value >&);
    Iterator erase(Iterator);
    Iterator begin() noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator cend() const noexcept;

  private:
    ForwardList< std::pair< Key, Value > > list_;
    bool isLess(const Key&, const Key&);
    bool isEqual(const Key&, const Key&);
  };

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::Iterator Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return list_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::ConstIterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return list_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::Iterator Dictionary< Key, Value, Compare >::end() noexcept
  {
    return list_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::ConstIterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return list_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< std::pair< Key, Value > > list)
  {
    for (auto&& pair: list)
    {
      push(pair.first, pair.second);
    }
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEmpty() const noexcept
  {
    return list_.isEmpty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::getSize() const noexcept
  {
    return list_.size();
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isLess(const Key& lhs, const Key& rhs)
  {
    return Compare()(lhs, rhs);
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEqual(const Key& lhs, const Key& rhs)
  {
    return (!isLess(lhs, rhs)) && (!isLess(rhs, lhs));
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    if (isEmpty())
    {
      list_.pushFront(std::pair< Key, Value >(k, v));
    }
    else
    {
      Iterator iter = list_.begin();
      while (iter != list_.end())
      {
        if (isEqual(iter->first, k))
        {
          throw std::logic_error("Can't push");
        }
        if (!isLess(iter->first, k))
        {
          break;
        }
        iter++;
      }
      const std::pair< Key, Value > p(k, v);
      list_.insert(p, iter);
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::Iterator Dictionary< Key, Value, Compare >::find(const Key& k)
  {
    Iterator iter = list_.begin();
    while (iter != list_.end())
    {
      if (isEqual(iter->first, k))
      {
        return iter;
      }
      iter++;
    }
    return iter;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::ConstIterator Dictionary< Key, Value, Compare >::find(const Key& k) const
  {
    return ConstIterator(find(k));
  }

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(const Key& k)
  {
    ConstIterator iter = find(k);
    if (iter != end())
    {
      return(iter->second);
    }
    else
    {
      throw std::logic_error("Key doesn't exist");
    }
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::drop(Key k)
  {
    ConstIterator iter = this->find(k);
    if (iter == end())
    {
      throw std::logic_error("Key doesn't exist");
    }
    list_.erase(iter);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::pairIterBool Dictionary< Key, Value, Compare >::insert(const std::pair< Key, Value >& p)
  {
    Iterator iter = begin();
    if (isEmpty())
    {
      list_.pushBack(p);
      return { list_.begin(), true };
    }
    while ((iter != end()) && (isLess(iter->first, p.first)))
    {
      iter++;
    }
    if ((iter != end()) && isEqual(p.first, iter->first))
    {
      return { iter, false };
    }
    list_.insert(p, iter);
    return { iter, true };
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::Iterator Dictionary< Key, Value, Compare >::erase(Iterator iter)
  {
    if (iter == end())
    {
      throw std::logic_error("Empty list");
    }
    auto tempKey = iter->first;
    list_.erase(iter);
    if (isEmpty())
    {
      return end();
    }
    Iterator tempIter = begin();
    while (tempIter != end() && (isLess(tempIter->first, tempKey)))
    {
      tempIter++;
    }
    return tempIter;
  }
}
#endif
