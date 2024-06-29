#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename K, typename V>
class tree {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  tree() noexcept;
  explicit tree(const value_type &elem) noexcept;
  tree(std::initializer_list<value_type> const &items);
  tree(const tree &other) noexcept;
  tree(tree &&other) noexcept;
  virtual ~tree();
  tree &operator=(const tree &other) noexcept;
  tree &operator=(tree &&other) noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  void swap(tree &other);
  void merge(tree<K, V> &other) noexcept;

  bool contains(const key_type &key) const noexcept;

 protected:
  typedef struct Node_ {
    value_type element_;
    unsigned char height_;
    Node_(const value_type &elem) : element_(elem), height_(1) {}
  } Node_;

  Node_ *root_;
  tree *parent_;
  tree *left_;
  tree *right_;

  class ConstIterator {
   public:
    ConstIterator() noexcept : tree_(nullptr) {}
    ConstIterator(const ConstIterator &other) { tree_ = other.tree_; }
    ConstIterator(tree<K, V> *tree) noexcept : tree_(tree) {}

    ConstIterator operator++(int);
    ConstIterator operator--(int);
    ConstIterator operator++();
    ConstIterator operator--();
    ConstIterator operator+=(size_type n);
    ConstIterator operator-=(size_type n);
    const value_type *operator->();
    bool operator==(const ConstIterator &other);
    bool operator!=(const ConstIterator &other);

    tree<K, V> *getTree() { return tree_; }
    Node_ *getNode() { return tree_->root_; }
    void setTree(tree<K, V> *new_tree) noexcept { tree_ = new_tree; }

   protected:
    tree<K, V> *tree_;
    void increment();
    void decrement();
  };

  class Iterator : public ConstIterator {
   public:
    Iterator() noexcept : ConstIterator() {}
    explicit Iterator(tree<K, V> *tree) noexcept : ConstIterator(tree) {}
    value_type *operator->();
  };

  void insertElem(const value_type &elem, Iterator &iter,
                  bool &is_inserted) noexcept;
  tree *findMin(const tree *node) const;
  tree *findMax(const tree *node) const;
  void multiSetInsert(const value_type &elem, Iterator &iter,
                      bool &is_inserted) noexcept;

 private:
  unsigned char getHeight(tree *tree);
  int getBalance();
  void updateHeight();
  void changePointers(tree<K, V> *temp, bool is_left);
  void leftRotate();
  void rightRotate();
  void balance();
  void getSize(int &size) const noexcept;
  void swapTrees(tree<K, V> &other);
  void searchKey(const K &key, bool &contains) const noexcept;
  void removeThis(tree<K, V> *current);
  void removeEdge(tree<K, V> *current, tree<K, V> *parent);
  void removeNode(tree<K, V> *current, tree<K, V> *parent);

 public:
  using const_iterator = ConstIterator;
  using iterator = Iterator;

  iterator begin() const;
  iterator end() const;

  virtual std::pair<iterator, bool> insert(const value_type &value) noexcept;
  void erase(iterator pos);

  tree<K, V> *getTreeWithIter(iterator pos) { return pos.getTree(); }
  Node_ *getNodeWithIter(iterator pos) { return pos.getNode(); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
}  // namespace s21

#include "s21_tree.tpp"
#include "s21_tree_iterators.tpp"

#endif