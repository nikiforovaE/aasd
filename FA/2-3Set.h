#ifndef TREESET_H
#define TREESET_H
#include "2-3Tree.h"

namespace nikiforova {

  template < typename Key, typename Value = Key, typename Compare = std::less< Key > >
  class TreeSet {
  public:
    using Iterator = typename Tree< Key, Value, Compare >::Iterator;
    using ConstIterator = typename Tree< Key, Value, Compare >::ConstIterator;
    using pairIterBool = typename std::pair< Iterator, bool >;
    using thisTreeNode_t = typename detail::treeNode_t< std::pair< Key, Value > >;
    pairIterBool insert(const Value&);
    pairIterBool insert(const std::pair< Key, Value >&);
    pairIterBool insert(const Key&, const Value&);
    void push(const Value& val);
    void push(const Key&, const Value&);
    void drop(const Key&);
    bool isEmpty() const;
    Iterator find(const Key&);
    ConstIterator cfind(const Key&) const;
    Iterator begin() const noexcept;
    Iterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    bool isLess(const Key& lhs, const Key& rhs) const;
    bool isEqual(const Key& lhs, const Key& rhs) const;

  private:
    Tree< Key, Value, Compare > tree_;
    thisTreeNode_t* searchNode(const Key&) const;
  };

  template < typename Key, typename Value, typename Compare >
  bool TreeSet< Key, Value, Compare >::isLess(const Key& lhs, const Key& rhs) const
  {
    return Compare()(lhs, rhs);
  }

  template < typename Key, typename Value, typename Compare >
  bool TreeSet< Key, Value, Compare >::isEqual(const Key& lhs, const Key& rhs) const
  {
    return (!isLess(lhs, rhs)) && (!isLess(rhs, lhs));
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::pairIterBool TreeSet< Key, Value, Compare >::insert(const Value& val)
  {
    return tree_.insert(val, val);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::pairIterBool TreeSet< Key, Value, Compare >::insert(const std::pair< Key, Value >& data)
  {
    return tree_.insert(data);
  }

  template< typename Key, typename Value, typename Compare >
  void TreeSet< Key, Value, Compare >::push(const Value& val)
  {
    tree_.push(val, val);
  }

  template< typename Key, typename Value, typename Compare >
  void TreeSet< Key, Value, Compare >::push(const Key& key, const Value& val)
  {
    tree_.push(key, val);
  }

  template< typename Key, typename Value, typename Compare >
  void nikiforova::TreeSet< Key, Value, Compare >::drop(const Key& key)
  {
    tree_.drop(key);
  }

  template< typename Key, typename Value, typename Compare >
  bool TreeSet< Key, Value, Compare >::isEmpty() const
  {
    return tree_.isEmpty();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::Iterator nikiforova::TreeSet< Key, Value, Compare >::find(const Key& key)
  {
    return tree_.find(key);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::ConstIterator nikiforova::TreeSet< Key, Value, Compare >::cfind(const Key& key) const
  {
    return tree_.cfind(key);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::thisTreeNode_t* nikiforova::TreeSet< Key, Value, Compare >::searchNode(const Key& key) const
  {
    return tree_.searchNode(key);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::Iterator TreeSet< Key, Value, Compare >::begin() const noexcept
  {
    return tree_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::Iterator TreeSet< Key, Value, Compare >::end() const noexcept
  {
    return tree_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::ConstIterator TreeSet< Key, Value, Compare >::cbegin() const noexcept
  {
    return tree_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeSet< Key, Value, Compare >::ConstIterator TreeSet< Key, Value, Compare >::cend() const noexcept
  {
    return tree_.cend();
  }

}

#endif
