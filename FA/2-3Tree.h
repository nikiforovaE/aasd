#ifndef TREE_H
#define TREE_H
#include <utility>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include "stack.h"
#include "queue.h"

namespace nikiforova {

  namespace detail {
    template< typename T >
    struct treeNode_t {
      T data_[3];
      size_t size_;
      treeNode_t* parent_;
      treeNode_t* first_;
      treeNode_t* second_;
      treeNode_t* third_;
      treeNode_t* fourth_;
      treeNode_t():
        size_(0),
        parent_(nullptr),
        first_(nullptr),
        second_(nullptr),
        third_(nullptr),
        fourth_(nullptr)
      {}
      treeNode_t(const T& x):
        size_(1),
        parent_(nullptr),
        first_(nullptr),
        second_(nullptr),
        third_(nullptr),
        fourth_(nullptr)
      {
        data_[0] = x;
      }
      treeNode_t(const treeNode_t& rhs):
        size_(rhs.size_),
        parent_(nullptr),
        first_(nullptr),
        second_(nullptr),
        third_(nullptr),
        fourth_(nullptr)
      {
        for (auto i = 0; i < rhs.size_; i++)
        {
          data_[i] = rhs.data_[i];
        }
      }
      ~treeNode_t() = default;
    };
  }

  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree {
  public:
    class ConstIterator;
    class Iterator;
    using pairIterBool = std::pair< typename Tree< Key, Value, Compare >::Iterator, bool >;
    using thisTreeNode_t = detail::treeNode_t< std::pair< Key, Value > >;
    Tree();
    Tree(std::initializer_list< std::pair< Key, Value > >);
    Tree(const Tree&);
    Tree(Tree&&) noexcept;
    ~Tree();

    Tree& operator= (const Tree&);
    Tree& operator= (Tree&&) noexcept;

    bool isEmpty() const noexcept;
    void clear();
    void swap(Tree&) noexcept;
    const Value get(const Key&);
    void push(const Key&, const Value&);
    void drop(const Key&);
    void fixErase(thisTreeNode_t*);
    void rotate(thisTreeNode_t*);
    void rotateAndMerge(thisTreeNode_t*);
    void merge(thisTreeNode_t*);
    void clearNode(thisTreeNode_t*);
    void sortKeys(thisTreeNode_t*);
    Iterator find(const Key&);
    ConstIterator cfind(const Key&) const;
    pairIterBool insert(const std::pair< Key, Value >&);
    pairIterBool insert(const Key&, const Value&);
    Iterator begin() const noexcept;
    Iterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    template < typename F >
    F traverse_lnr(F f) const;

    template < typename F >
    F traverse_rnl(F f) const;

    template < typename F >
    F traverse_breadth(F f) const;

    class ConstIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
    {
    public:
      friend class Tree< Key, Value, Compare >;
      ConstIterator(const ConstIterator&) = default;
      ConstIterator& operator=(const ConstIterator&) = default;
      ~ConstIterator() = default;
      ConstIterator& operator++()
      {
        assert(treeNode_ != nullptr);
        if (treeNode_->first_)
        {
          if (treeNode_->size_ == 1)
          {
            treeNode_ = treeNode_->second_;
            index_ = 0;
            while (treeNode_->first_)
            {
              treeNode_ = treeNode_->first_;
              index_ = 0;
            }
            return *this;
          }
          if (treeNode_->size_ == 2)
          {
            if (index_ == 0)
            {
              treeNode_ = treeNode_->second_;
              index_ = 0;
            }
            else
            {
              treeNode_ = treeNode_->third_;
              index_ = 0;
            }
            while (treeNode_->first_)
            {
              treeNode_ = treeNode_->first_;
            }
            return *this;
          }
        }
        else
        {
          if (treeNode_->size_ == 2 && index_ == 0)
          {
            index_ = 1;
            return *this;
          }
          if (!treeNode_->parent_)
          {
            if ((treeNode_->size_ == 1 && index_ == 0) || (treeNode_->size_ == 2 && index_ == 1))
            {
              *this = ConstIterator(nullptr);
              return *this;
            }
          }
          else
          {
            while (treeNode_ == treeNode_->parent_->third_ || (treeNode_->parent_->size_ == 1 && treeNode_ == treeNode_->parent_->second_))
            {
              treeNode_ = treeNode_->parent_;
              if (!treeNode_->parent_)
              {
                *this = ConstIterator(nullptr);
                return *this;
              }
            }
            if (treeNode_ == treeNode_->parent_->first_)
            {
              treeNode_ = treeNode_->parent_;
              index_ = 0;
              return *this;
            }
            else if ((treeNode_->parent_->size_ == 2) && (treeNode_ == treeNode_->parent_->second_))
            {
              treeNode_ = treeNode_->parent_;
              index_ = 1;
              return *this;
            }
          }
        }
        *this = ConstIterator(nullptr);
        return *this;
      }
      ConstIterator operator++(int)
      {
        assert(treeNode_ != nullptr);
        ConstIterator result(*this);
        ++(*this);
        return result;
      }
      ConstIterator& operator--()
      {
        assert(treeNode_ != nullptr);
        if (!treeNode_->second_)
        {
          if ((treeNode_->size_ == 2) && index_ == 1)
          {
            index_ = 0;
            return *this;
          }
          else if (treeNode_ == treeNode_->parent_->third_)
          {
            treeNode_ = treeNode_->parent_;
            index_ = 1;
          }
          else if (treeNode_ == treeNode_->parent_->second_)
          {
            treeNode_ = treeNode_->parent_;
            index_ = 0;
          }
          else
          {
            if (treeNode_->parent_->parent_ && treeNode_->parent_ == treeNode_->parent_->parent_->third_)
            {
              treeNode_ = treeNode_->parent_->parent_;
              index_ = 1;
            }
            else if (treeNode_->parent_ == treeNode_->parent_->parent_->second_)
            {
              treeNode_ = treeNode_->parent_->parent_;
              index_ = 0;
            }
          }
          return *this;
        }
        else
        {
          if (index_ = 0)
          {
            treeNode_ = treeNode_->first_;
          }
          else
          {
            treeNode_ = treeNode_->second_;
          }
          if (treeNode_->size_ == 2)
          {
            index_ = 1;
          }
          else
          {
            index_ = 0;
          }
          ConstIterator iter = treeNode_;
          while (treeNode_->first_)
          {
            iter++;
          }
          *this = iter;
          return *this;
        }
      }
      ConstIterator operator--(int)
      {
        assert(treeNode_ != nullptr);
        ConstIterator result(*this);
        --(*this);
        return result;
      }
      const std::pair< Key, Value >& operator*() const
      {
        assert(treeNode_ != nullptr);
        return treeNode_->data_[index_];
      }
      const std::pair< Key, Value >* operator->() const
      {
        assert(treeNode_ != nullptr);
        return std::addressof(treeNode_->data_[index_]);
      }
      bool operator==(const ConstIterator& rhs) const
      {
        return (treeNode_ == rhs.treeNode_) && ((index_ == rhs.index_) || (treeNode_ == nullptr));
      }
      bool operator!=(const ConstIterator& rhs) const
      {
        return !(rhs == *this);
      }
    private:
      const thisTreeNode_t* treeNode_;
      int index_;
      ConstIterator(thisTreeNode_t* rhs)
      {
        treeNode_ = rhs;
        index_ = 0;
      }
    };

    class Iterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
    {
    public:
      friend class Tree< Key, Value, Compare >;
      Iterator(const Iterator&) = default;
      Iterator& operator=(const Iterator&) = default;
      ~Iterator() = default;
      Iterator(const ConstIterator& x):
        cIter_(x)
      {}
      Iterator& operator++()
      {
        ++cIter_;
        return *this;
      }
      Iterator operator++(int)
      {
        Iterator result(*this);
        ++(*this);
        return result;
      }
      Iterator& operator--()
      {
        --cIter_;
        return *this;
      }
      Iterator operator--(int)
      {
        Iterator result(*this);
        --(*this);
        return result;
      }
      std::pair< Key, Value >& operator*() const
      {
        return const_cast<std::pair< Key, Value >&>(*cIter_);
      }
      std::pair< Key, Value >* operator->() const
      {
        return const_cast<std::pair< Key, Value >*>(std::addressof(*cIter_));
      }
      bool operator==(const Iterator& rhs) const
      {
        return cIter_ == rhs.cIter_;
      }
      bool operator!=(const Iterator& rhs) const
      {
        return !(rhs == *this);
      }

    private:
      ConstIterator cIter_;
    };

  private:
    thisTreeNode_t* root_;
    bool isLess(const Key&, const Key&) const;
    bool isEqual(const Key&, const Key&) const;
    thisTreeNode_t* findMinNode(thisTreeNode_t*);
    thisTreeNode_t* findMaxNode(thisTreeNode_t*);
    thisTreeNode_t* splitNode(thisTreeNode_t*);
    thisTreeNode_t* searchNode(const Key&) const;
  };

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >::Tree():
    root_(nullptr)
  {}

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >::Tree(std::initializer_list< std::pair< Key, Value > > list):
    root_(nullptr)
  {
    for (auto&& pair: list)
    {
      insert(pair);
    }
  }

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >::Tree(const Tree& rhs):
    root_(nullptr)
  {
    if (!rhs.isEmpty())
    {
      Iterator iter = rhs.begin();
      try
      {
        while (iter != rhs.end())
        {
          insert(*iter);
          iter++;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >::Tree(Tree&& rhs) noexcept:
    root_(rhs.root_)
  {
    rhs.root_ = nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >& Tree< Key, Value, Compare >::operator=(const Tree< Key, Value, Compare >& rhs)
  {
    if (this != std::addressof(rhs))
    {
      Tree< Key, Value, Compare > temp(rhs);
      swap(temp);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >& Tree< Key, Value, Compare >::operator=(Tree< Key, Value, Compare >&& rhs) noexcept
  {
    if (this != std::addressof(rhs))
    {
      Tree< Key, Value, Compare > temp(std::move(rhs));
      swap(temp);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Tree< Key, Value, Compare >::~Tree()
  {
    clear();
  }

  template< typename Key, typename Value, typename Compare >
  bool Tree< Key, Value, Compare >::isEmpty() const noexcept
  {
    return !root_;
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::clear()
  {
    clearNode(root_);
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::swap(Tree& rhs) noexcept
  {
    std::swap(root_, rhs.root_);
  }

  template< typename Key, typename Value, typename Compare >
  const Value Tree< Key, Value, Compare >::get(const Key& key)
  {
    auto iter = cfind(key);
    return (*iter).second;
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::push(const Key& key, const Value& val)
  {
    insert(key, val);
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::drop(const Key& key)
  {
    thisTreeNode_t* node = searchNode(key);
    if (node == nullptr)
    {
      return;
    }
    else if (node->size_ == 2 && !node->first_)
    {
      if (node->data_[0].first == key)
      {
        node->data_[0] = node->data_[1];
      }
      node->size_--;
      return;
    }
    if (node->first_)
    {
      thisTreeNode_t* minNode = nullptr;
      if (key == node->data_[0].first)
      {
        minNode = findMinNode(node->second_);
      }
      else
      {
        minNode = findMinNode(node->third_);
      }
      std::pair< Key, Value >& data = (key == node->data_[0].first) ? node->data_[0] : node->data_[1];
      auto temp = minNode->data_[0];
      minNode->data_[0] = data;
      data = temp;
      node = minNode;
    }
    if (node->size_ == 2 && key == node->data_[0].first)
    {
      node->data_[0] = node->data_[1];
    }
    node->size_--;
    if (node->size_ == 1 && !node->first_)
    {
      return;
    }
    if (node->size_ == 0)
    {
      fixErase(node);
    }
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::fixErase(thisTreeNode_t* node)
  {
    if (node->size_ == 0 && node->parent_ == nullptr && !node->first_)
    {
      delete node;
      node = nullptr;
      root_ = nullptr;
    }
    else
    {
      thisTreeNode_t* parent = node->parent_;
      if (node->parent_)
      {
        if (parent->size_ == 1)
        {
          if (node == parent->second_ && parent->first_->size_ == 1)
          {
            merge(node);
          }
          else if (node == parent->first_ && parent->second_->size_ == 1)
          {
            merge(node);
          }
          else if (node == parent->first_ && parent->second_->size_ == 2)
          {
            rotate(node);
          }
          else if (node == parent->second_ && parent->first_->size_ == 2)
          {
            rotate(node);
          }
        }
        else if (parent->size_ == 2)
        {
          if (parent->second_->size_ == 1 || parent->second_->size_ == 0)
          {
            if (node == parent->first_ || node == parent->third_)
            {
              rotateAndMerge(node);
              return;
            }
            else if (parent->first_->size_ == 1 && parent->third_->size_ == 1)
            {
              rotateAndMerge(node);
              return;
            }
          }
          rotate(node);
        }
      }
      else
      {
        thisTreeNode_t *tmp = nullptr;
        if (node->first_ != nullptr)
        {
          tmp = node->first_;
        }
        else
        {
          tmp = node->second_;
        }
        tmp->parent_ = nullptr;
        delete node;
        root_ = tmp;
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::rotate(thisTreeNode_t* node)
  {
    thisTreeNode_t* parent = node->parent_;
    if (node == parent->first_)
    {
      node->data_[0] = parent->data_[0];
      node->size_++;
      parent->data_[0] = parent->second_->data_[0];
      parent->second_->data_[0] = parent->second_->data_[1];
      parent->second_->size_--;
      if (parent->second_->first_)
      {
        node->second_ = parent->second_->first_;
        node->second_->parent_ = node;
        parent->second_->first_ = parent->second_->second_;
        parent->second_->second_ = parent->second_->third_;
        parent->second_->third_ = nullptr;
      }
    }
    else if (node == parent->second_)
    {
      if (parent->first_->size_ == 2)
      {
        node->data_[0] = parent->data_[0];
        node->size_++;
        node->parent_->data_[0] = parent->first_->data_[1];
        parent->first_->size_--;
        if (node->first_)
        {
          node->second_ = node->first_;
          node->first_ = parent->first_->third_;
          if (node->first_)
          {
            node->first_->parent_ = node;
          }
          parent->first_->third_ = nullptr;
        }
      }
      else if (parent->third_->size_ == 2)
      {
        node->data_[0] = parent->data_[1];
        node->size_++;
        parent->data_[1] = parent->third_->data_[0];
        parent->third_->data_[0] = parent->third_->data_[1];
        parent->third_->size_--;
        if (node->first_)
        {
          node->second_ = parent->third_->first_;
          node->second_->parent_ = node;
          parent->third_->first_ = parent->third_->second_;
          parent->third_->second_ = parent->third_->third_;
          parent->third_->third_ = nullptr;
        }
      }
    }
    else
    {
      node->data_[0] = parent->data_[1];
      node->size_++;
      parent->data_[1] = parent->second_->data_[1];
      parent->second_->size_--;
      if (node->first_)
      {
        node->second_ = node->first_;
        node->first_ = parent->second_->third_;
        node->first_->parent_ = node;
        parent->third_ = nullptr;
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::rotateAndMerge(thisTreeNode_t* node)
  {
    thisTreeNode_t* parent = node->parent_;
    if (node == parent->first_)
    {
      parent->second_->data_[1] = parent->second_->data_[0];
      parent->second_->data_[0] = parent->data_[0];
      parent->data_[0] = parent->data_[1];
      parent->second_->size_++;
      parent->second_->third_ = parent->second_->second_;
      parent->second_->second_ = parent->second_->first_;
      if (node->first_)
      {
        parent->second_->first_ = node->first_;
        parent->second_->first_->parent_ = parent->second_;
      }
      delete node;
      parent->first_ = parent->second_;
      parent->second_ = parent->third_;
    }
    else
    {
      if (node == parent->second_)
      {
        parent->third_->data_[1] = parent->third_->data_[0];
        parent->third_->data_[0] = parent->data_[1];
        parent->third_->parent_ = parent;
        if (node->first_)
        {
          parent->third_->third_ = parent->third_->second_;
          parent->third_->second_ = parent->third_->first_;
          parent->third_->first_ = node->first_;
          parent->third_->first_->parent_ = parent->third_;
        }
        delete node;
        parent->second_ = parent->third_;
      }
      else
      {
        delete node;
        parent->second_->data_[1] = parent->data_[1];
      }
      parent->second_->size_++;
    }
    parent->size_--;
    parent->third_ = nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::merge(thisTreeNode_t* node)
  {
    thisTreeNode_t* parent = node->parent_;
    if (node == parent->first_)
    {
      parent->second_->data_[1] = parent->second_->data_[0];
      parent->second_->data_[0] = parent->data_[0];
      parent->size_--;
      parent->second_->size_++;
      if (node->first_)
      {
        parent->second_->third_ = parent->second_->second_;
        parent->second_->second_ = parent->second_->first_;
        parent->second_->first_ = node->first_;
        parent->second_->first_->parent_ = parent->second_;
        node->first_ = nullptr;
      }
      delete node;
      parent->first_ = parent->second_;
      parent->second_ = nullptr;
    }
    else
    {
      parent->first_->data_[1]=parent->data_[0];
      parent->first_->size_++;
      parent->size_--;
      if (node->first_)
      {
        parent->first_->third_ = node->first_;
        parent->first_->third_->parent_ = parent->first_;
        node->first_ = nullptr;
      }
      delete node;
      parent->second_ = nullptr;
    }
    return fixErase(parent);
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::thisTreeNode_t* Tree< Key, Value, Compare >::findMinNode(thisTreeNode_t* node)
  {
    thisTreeNode_t* res = node;
    if (!res)
    {
      return res;
    }
    while (res->first_)
    {
      res = res->first_;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::thisTreeNode_t* Tree< Key, Value, Compare >::findMaxNode(thisTreeNode_t* node)
  {
    thisTreeNode_t* res = node;
    while (res->first_)
    {
      if (res->size_ == 2)
      {
        res = res->third_;
      }
      else
      {
        res = res->second_;
      }
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::clearNode(thisTreeNode_t* node)
  {
    if (node)
    {
      clearNode(node->first_);
      clearNode(node->second_);
      clearNode(node->third_);
      delete node;
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::thisTreeNode_t* Tree< Key, Value, Compare >::splitNode(thisTreeNode_t* node)
  {
    if (node->size_ != 3)
    {
      return node;
    }
    thisTreeNode_t* left = new thisTreeNode_t;
    left->data_[0] = node->data_[0];
    left->parent_ = node->parent_;
    left->first_ = node->first_;
    left->second_ = node->second_;
    if (left->first_)
    {
      left->first_->parent_ = left;
    }
    if (left->second_)
    {
      left->second_->parent_ = left;
    }
    left->size_ = 1;
    thisTreeNode_t* right = new thisTreeNode_t;
    right->data_[0] = node->data_[2];
    right->parent_ = node->parent_;
    right->first_ = node->third_;
    right->second_ = node->fourth_;
    if (right->first_)
    {
      right->first_->parent_ = right;
    }
    if (right->second_)
    {
      right->second_->parent_ = right;
    }
    right->size_ = 1;
    if (node->parent_)
    {
      node->parent_->data_[node->parent_->size_] = node->data_[1];
      node->parent_->size_++;
      sortKeys(node->parent_);
      if (node == node->parent_->first_)
      {
        node->parent_->first_ = left;
        node->parent_->fourth_ = node->parent_->third_;
        node->parent_->third_ = node->parent_->second_;
        node->parent_->second_ = right;
      }
      else if (node == node->parent_->second_)
      {
        node->parent_->second_ = left;
        node->parent_->fourth_ = node->parent_->third_;
        node->parent_->third_ = right;
      }
      else
      {
        node->parent_->third_ = left;
        node->parent_->fourth_ = right;
      }
      thisTreeNode_t* temp = node->parent_;
      delete node;
      return splitNode(temp);
    }
    left->parent_ = node;
    right->parent_ = node;
    node->data_[0] = node->data_[1];
    node->size_ = 1;
    node->parent_ = nullptr;
    node->first_ = left;
    node->second_ = right;
    node->third_ = nullptr;
    node->fourth_ = nullptr;
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  void Tree< Key, Value, Compare >::sortKeys(thisTreeNode_t* node)
  {
    if (!isLess(node->data_[0].first, node->data_[1].first))
    {
      std::swap(node->data_[0], node->data_[1]);
    }
    if (node->size_ == 3)
    {
      if (!isLess(node->data_[0].first, node->data_[2].first))
      {
        std::swap(node->data_[0], node->data_[2]);
      }
      if (!isLess(node->data_[1].first, node->data_[2].first))
      {
        std::swap(node->data_[1], node->data_[2]);
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::Iterator Tree< Key, Value, Compare >::find(const Key& key)
  {
    return Iterator(cfind(key));
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::thisTreeNode_t* Tree< Key, Value, Compare >::searchNode(const Key& key) const
  {
    if (!root_)
    {
      return root_;
    }
    thisTreeNode_t* node = root_;
    while (node && !(isEqual(key, node->data_[0].first) || (node->size_ == 2 && isEqual(key, node->data_[1].first))))
    {
      if (isLess(key, node->data_[0].first))
      {
        node = node->first_;
      }
      else if (node->size_ == 1 && !isLess(key, node->data_[0].first))
      {
        node = node->second_;
      }
      else if (node->size_ == 2 && isLess(key, node->data_[1].first))
      {
        node = node->second_;
      }
      else if (node->size_ == 2 && !isLess(key, node->data_[1].first))
      {
        if (node->first_)
        {
          node = node->third_;
        }
        else
        {
          return node;
        }
      }
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::ConstIterator Tree< Key, Value, Compare >::cfind(const Key& key) const
  {
    if (!root_)
    {
      return cend();
    }
    thisTreeNode_t* node = root_;
    while (node)
    {
      if (isEqual(key, node->data_[0].first))
      {
        auto res = ConstIterator(node);
        res.index_ = 0;
        return res;
      }
      else if (isEqual(key, node->data_[1].first))
      {
        auto res = ConstIterator(node);
        res.index_ = 1;
        return res;
      }
      if (isLess(key, node->data_[0].first))
      {
        node = node->first_;
      }
      else if ((node->size_ == 1 && !isLess(key, node->data_[0].first)) || (node->size_ == 2 && isLess(key, node->data_[1].first)))
      {
        node = node->second_;
      }
      else if (node->size_ == 2 && !isLess(key, node->data_[1].first))
      {
        if (node->first_)
        {
          node = node->third_;
        }
        else
        {
          return ConstIterator(nullptr);
        }
      }
    }
    return ConstIterator(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::pairIterBool Tree< Key, Value, Compare >::insert(const std::pair< Key, Value >& data)
  {
    return insert(data.first, data.second);
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::pairIterBool Tree< Key, Value, Compare >::insert(const Key& key, const Value& value)
  {
    std::pair< Key, Value > pair = std::make_pair(key, value);
    thisTreeNode_t* prevNode = root_;
    if (isEmpty())
    {
      root_ = new thisTreeNode_t(pair);
      return std::make_pair(Iterator(root_), true);
    }
    else
    {
      auto size = prevNode->size_;
      while (prevNode != nullptr && !(isEqual(key, prevNode->data_[0].first) || (size == 2 && isEqual(key, prevNode->data_[1].first))))
      {
        if (isLess(key, prevNode->data_[0].first))
        {
          if (!prevNode->first_)
          {
            prevNode->data_[prevNode->size_] = pair;
            prevNode->size_++;
            sortKeys(prevNode);
            splitNode(prevNode);
            return std::make_pair(Iterator(prevNode), true);
          }
          else
          {
            prevNode = prevNode->first_;
            size = prevNode->size_;
          }
        }
        else if ((!isLess(key, prevNode->data_[0].first) && isLess(key, prevNode->data_[1].first) && size == 2 ) || size == 1)
        {
          if (!prevNode->first_)
          {
            prevNode->data_[prevNode->size_] = pair;
            prevNode->size_++;
            sortKeys(prevNode);
            splitNode(prevNode);
            return std::make_pair(Iterator(prevNode), true);
          }
          else
          {
            prevNode = prevNode->second_;
            size = prevNode->size_;
          }
        }
        else if (size == 2 && !isLess(key, prevNode->data_[1].first))
        {
          if (!prevNode->first_)
          {
            prevNode->data_[prevNode->size_] = pair;
            prevNode->size_++;
            sortKeys(prevNode);
            splitNode(prevNode);
            return std::make_pair(Iterator(prevNode), true);
          }
          else
          {
            prevNode = prevNode->third_;
            size = prevNode->size_;
          }
        }
      }
    }
    return std::make_pair(Iterator(prevNode), false);
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::Iterator Tree< Key, Value, Compare >::begin() const noexcept
  {
    return Iterator(cbegin());
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::Iterator Tree< Key, Value, Compare >::end() const noexcept
  {
    return Iterator(cend());
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::ConstIterator Tree< Key, Value, Compare >::cbegin() const noexcept
  {
    if (!root_)
    {
      return ConstIterator(root_);
    }
    else
    {
      thisTreeNode_t* temp = root_;
      while (temp->first_)
      {
        temp = temp->first_;
      }
      return ConstIterator(temp);
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename Tree< Key, Value, Compare >::ConstIterator Tree< Key, Value, Compare >::cend() const noexcept
  {
    return ConstIterator(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  bool Tree< Key, Value, Compare >::isLess(const Key& lhs, const Key& rhs) const
  {
    return Compare()(lhs, rhs);
  }

  template< typename Key, typename Value, typename Compare >
  bool Tree< Key, Value, Compare >::isEqual(const Key& lhs, const Key& rhs) const
  {
    return (!isLess(lhs, rhs)) && (!isLess(rhs, lhs));
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F Tree< Key, Value, Compare >::traverse_lnr(F f) const
  {
    auto iter = cbegin();
    while (iter != cend())
    {
      f(*iter);
      iter++;
    }
    return f;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F Tree< Key, Value, Compare >::traverse_rnl(F f) const
  {
    auto iter = cbegin();
    Stack< std::pair< Key, Value > > stack;
    while (iter != cend())
    {
      stack.push(*iter);
      iter++;
    }
    while (!stack.isEmpty())
    {
      f(stack.getTop());
      stack.drop();
    }
    return f;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F Tree< Key, Value, Compare >::traverse_breadth(F f) const
  {
    if (!root_)
    {
      return f;
    }
    Queue< thisTreeNode_t* > queue;
    queue.push(root_);
    while (!queue.isEmpty())
    {
      thisTreeNode_t* tempNode = queue.getFront();
      f(tempNode->data_[0]);
      if (tempNode->size_ == 2)
      {
        f(tempNode->data_[1]);
      }
      if (tempNode->first_)
      {
        queue.push(tempNode->first_);
      }
      if (tempNode->second_)
      {
        queue.push(tempNode->second_);
      }
      if (tempNode->third_)
      {
        queue.push(tempNode->third_);
      }
      queue.drop();
    }
    return f;
  }
}
#endif
