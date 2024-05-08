
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> , virtual protected Vector<Data> {

private:

protected:

  struct NodeVec : virtual MutableBinaryTree<Data>::MutableNode { 

  friend class BinaryTreeVec<Data>;

  private:

    BinaryTreeVec<Data>* Tree = nullptr;
    unsigned long int index;

  protected:

  public:

    /* ************************************************************************** */

    // Specific constructor
    NodeVec(const Data &data, unsigned long int index, BinaryTreeVec<Data>* Tree);
    NodeVec(Data&& data, unsigned long int index, BinaryTreeVec<Data>* Tree) noexcept;

    /* ************************************************************************** */

    // Destructor
    inline virtual ~NodeVec() = default;

    /* ************************************************************************** */

    // Copy assignment
    inline NodeVec& operator=(const NodeVec& node) {
      Tree->data[index]=node.data[index];
      index = node.index;
      Tree = node.Tree;
      return *this;
    };

    // Move assignment
    inline NodeVec& operator=(NodeVec&& node) noexcept {
      std::swap(Tree->data[index], node.data[index]);
      std::swap(index, node.index);
      std::swap(Tree, node.Tree);
      return *this;
    };

    /* ************************************************************************** */

    // Specific member functions
    inline virtual Data& Element() noexcept override { return Tree->elements[index]; }
    inline virtual const Data& Element() const noexcept override { return Tree->elements[index]; }

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;

    virtual NodeVec& RightChild() override;
    virtual const NodeVec& RightChild() const override;

  };

  using Container::size;
  using Vector<Data>::elements;
  Vector<NodeVec*> NodeArray = Vector<NodeVec*>(0);

public:

  // Default constructor
  BinaryTreeVec() = default; 

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data>&&) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&); 

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();
  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeVec& btv) const noexcept { return Vector<Data>::operator==(btv); };  // type operator==(argument) specifiers;
  inline bool operator!=(const BinaryTreeVec& btv) const noexcept { return !(operator==(btv)); };   // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override;// Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  inline void BreadthTraverse(const TraverseFun fun) const override { BinaryTree<Data>::BreadthTraverse(fun); };  // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  
  using typename MappableContainer<Data>::MapFun;
  inline void BreadthMap(const MapFun map) override { MutableBinaryTree<Data>::BreadthMap(map); }; // Override BreadthMappableContainer member

  /* ************************************************************************** */

  inline void Traverse(const TraverseFun fun) const override { BinaryTree<Data>::Traverse(fun); };

  inline void PreOrderTraverse(TraverseFun fun) const override { BinaryTree<Data>::PreOrderTraverse(fun); };
  inline void PostOrderTraverse(TraverseFun fun) const override { BinaryTree<Data>::PostOrderTraverse(fun); };
  inline void InOrderTraverse(TraverseFun fun) const override { BinaryTree<Data>::InOrderTraverse(fun); };

  inline void PreOrderMap(MapFun map) override { MutableBinaryTree<Data>::PreOrderMap(map); };
  inline void PostOrderMap(MapFun map) override { MutableBinaryTree<Data>::PostOrderMap(map); };
  inline void Map(MapFun map) override { MutableBinaryTree<Data>::Map(map); };

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
