
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree  : virtual public PreOrderTraversableContainer<Data>, 
                    virtual public PostOrderTraversableContainer<Data>, 
                    virtual public InOrderTraversableContainer<Data>,   
                    virtual public BreadthTraversableContainer<Data> {  

private:

protected:

public:

  struct Node {

  protected:

    // Comparison operators
    inline bool operator==(const Node& iter) const noexcept { return (Element() == iter.Element()); }; // Comparison of abstract types is possible, but is not visible.
    inline bool operator!=(const Node& iter) const noexcept { return !(operator==(iter)); };  // Comparison of abstract types is possible, but is not visible.

  public:

    friend class BinaryTree<Data>; 

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node& iter) = delete;// Copy assignment of abstract types is not possible.

    // Move assignment
    Node& operator=(Node&& iter) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    inline virtual bool IsLeaf() const noexcept { return ((!HasLeftChild()) && (!HasRightChild())); }; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0;  // (concrete function should not throw exceptions)

    virtual const Node& LeftChild() const = 0;  // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;
  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree& iter) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree&& iter) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree& iter) const noexcept;  // Comparison of abstract binary tree is possible.
  inline bool operator!=(const BinaryTree& iter) const noexcept{ return !(operator==(iter)); }; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void Traverse(TraverseFun) const override;  // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  virtual void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  virtual void InOrderTraverse(TraverseFun) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  virtual void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

protected:

  // Auxiliary functions, if necessary!

  void PreOrderTraversable(const Node *node, TraverseFun fun) const;
  void PostOrderTraversable(const Node *node, TraverseFun fun) const; 
  void InOrderTraversable(const Node *node, TraverseFun fun) const;
  void BreadthTraversable(const Node *node, TraverseFun fun) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,   
                          virtual public BinaryTree<Data>, 
                          virtual public PreOrderMappableContainer<Data>,  
                          virtual public PostOrderMappableContainer<Data>, 
                          virtual public InOrderMappableContainer<Data>, 
                          virtual public BreadthMappableContainer<Data> { 

private:

protected:

public:

  struct MutableNode : virtual public BinaryTree<Data>::Node { 
    
    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default; 

    /* ********************************************************************** */

    // Copy assignment
    MutableNode& operator=(const MutableNode&) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode& operator=(MutableNode&&) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions
    using BinaryTree<Data>::Node::Element;
    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
    using BinaryTree<Data>::Node::LeftChild;
    virtual  MutableNode& LeftChild() = 0 ; // (concrete function must throw std::out_of_range when not existent)
    using BinaryTree<Data>::Node::RightChild;
    virtual MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default; 

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree<Data>& operator=(const MutableBinaryTree&) = delete;  // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableBinaryTree<Data>& operator=(MutableBinaryTree&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  using BinaryTree<Data>::Root;
  virtual MutableNode& Root() = 0;  // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun; 

  inline virtual void Map(MapFun fun) override { PreOrderMap(fun); }; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  virtual void InOrderMap(MapFun) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  virtual void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

  void PreOrderMappable(MutableNode* node, MapFun map);
  void PostOrderMappable(MutableNode* node, MapFun map); 
  void InOrderMappable(MutableNode* node, MapFun map); 
  void BreadthMappable(MutableNode* node, MapFun map); 

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> { 

private:

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* curr=nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&);  // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator&); 

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&&) noexcept; 

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator&); 

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator&) const noexcept; 
  inline bool operator!=(const BTPreOrderIterator& iter) const noexcept { return !(operator==(iter)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override { return (curr==nullptr); }; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  inline void Reset() noexcept override { stk.Clear(); curr=root; }; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTPreOrderIterator<Data> {

private:

protected:

public:

  // Specific constructors
  inline BTPreOrderMutableIterator(MutableBinaryTree<Data>& iter) : BTPreOrderIterator<Data>(iter){;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  inline BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& iter) : BTPreOrderIterator<Data>(iter) {;};

  // Move constructor
  inline BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& iter) noexcept : BTPreOrderIterator<Data>(std::move(iter)) {;};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  inline BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator&); 

  // Move assignment
  inline BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&&) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPreOrderMutableIterator& iter) const noexcept { return BTPreOrderIterator<Data>::operator==(iter); };  
  inline bool operator!=(const BTPreOrderMutableIterator& iter) const noexcept { return !(operator==(iter)); };  

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {  

private:

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* curr=nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stk;

  const typename BinaryTree<Data>::Node* LeftLeaf(const typename BinaryTree<Data>::Node* currentLeaf);

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>& iter); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator&);  

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&& iter) noexcept;  

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator<Data>&); 

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator<Data>&& iter) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator&) const noexcept;  
  inline bool operator!=(const BTPostOrderIterator& iter) const noexcept { return !(operator==(iter)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override;  // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override { return (curr==nullptr); }; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  inline void Reset() noexcept override { stk.Clear(); curr=LeftLeaf(root); }; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator: virtual public MutableIterator<Data>, virtual public BTPostOrderIterator<Data> { 

private:

protected:

public:

  // Specific constructors
  inline BTPostOrderMutableIterator(MutableBinaryTree<Data>& iter) : BTPostOrderIterator<Data>(iter) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  inline BTPostOrderMutableIterator(const BTPostOrderMutableIterator& iter) : BTPostOrderIterator<Data>(iter){;}; 

  // Move constructor
  inline BTPostOrderMutableIterator(BTPostOrderMutableIterator&& iter) noexcept : BTPostOrderIterator<Data>(std::move(iter)) {;}; 

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderMutableIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  inline BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator&); 

  // Move assignment
  inline BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&&) noexcept;  

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPostOrderMutableIterator& iter) const noexcept { return BTPostOrderIterator<Data>::operator==(iter); };
  inline bool operator!=(const BTPostOrderMutableIterator& iter) const noexcept { return !(operator==(iter)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> { 

private:

protected:

  const typename BinaryTree<Data>::Node* curr=nullptr;
  const typename BinaryTree<Data>::Node* root=nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stk;

  const typename BinaryTree<Data>::Node* FindLeftLeaf(const typename BinaryTree<Data>::Node*);


public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator&);  

  // Move constructor
  BTInOrderIterator(BTInOrderIterator&&) noexcept;  

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator&); 

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator&&) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator&) const noexcept; 
  inline bool operator!=(const BTInOrderIterator& iter) const noexcept { return !(operator==(iter)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override { return (curr==nullptr); }; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  inline void Reset() noexcept override { stk.Clear(); curr=FindLeftLeaf(root); }; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTInOrderIterator<Data> {

private:

protected:

public:

  // Specific constructors
  inline BTInOrderMutableIterator(MutableBinaryTree<Data>& iter) : BTInOrderIterator<Data>(iter) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  inline BTInOrderMutableIterator(const BTInOrderMutableIterator& iter) : BTInOrderIterator<Data>(iter) {;};  

  // Move constructor
  inline BTInOrderMutableIterator(BTInOrderMutableIterator&& iter) noexcept : BTInOrderIterator<Data>(std::move(iter)) {;}; 

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator&); 

  // Move assignment
  inline BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTInOrderMutableIterator& iter) const noexcept { return BTInOrderIterator<Data>::operator==(iter); };
  inline bool operator!=(const BTInOrderMutableIterator& iter) const noexcept { return !(operator==(iter)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override;  // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> { 

private:

protected:

  const typename BinaryTree<Data>::Node* curr=nullptr;
  const typename BinaryTree<Data>::Node* root=nullptr;
  QueueLst<const typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&); //An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator&);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator&); 

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator&&) noexcept;  

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator&) const noexcept;  
  inline bool operator!=(const BTBreadthIterator& iter) const noexcept { return !(operator==(iter)); } 

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override { return (curr==nullptr); }; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  inline void Reset() noexcept override { queue.Clear(); curr=root; }; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>, virtual public BTBreadthIterator<Data> {

private:

protected:

public:

  // Specific constructors
  inline BTBreadthMutableIterator(MutableBinaryTree<Data>& iter) : BTBreadthIterator<Data>(iter) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  inline BTBreadthMutableIterator(const BTBreadthMutableIterator& iter) : BTBreadthIterator<Data>(iter) {;}; 

  // Move constructor
  inline BTBreadthMutableIterator(BTBreadthMutableIterator&& iter) noexcept : BTBreadthIterator<Data>(std::move(iter)) {;};  

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthMutableIterator() = default; 

  /* ************************************************************************ */

  // Copy assignment
  inline BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator&);

  // Move assignment
  inline BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&&) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTBreadthMutableIterator& iter) const noexcept { return BTBreadthIterator<Data>::operator==(iter); };
  inline bool operator!=(const BTBreadthMutableIterator& iter) const noexcept { return !(operator==(iter)); }; 

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override;  // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
