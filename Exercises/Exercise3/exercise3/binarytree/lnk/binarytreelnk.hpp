
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {  

private:

protected:

  using Container::size;

  using typename BinaryTree<Data>::Node;

  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode { 

    friend class BinaryTreeLnk<Data>;

  private:

  protected:

  public:

    Data elem {};
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;

    /* ************************************************************************** */

    // Specific constructors
    NodeLnk(const Data& data) : elem(data) {};
    NodeLnk(Data&& data) noexcept { std::swap(elem , data); };

    /* ************************************************************************** */

    // Copy constructor
    NodeLnk(const NodeLnk&);

    // Move constructor
    NodeLnk(NodeLnk&&) noexcept;

    /* ************************************************************************** */

    // Destructor
    inline virtual ~NodeLnk() { delete left; delete right; };

    /* ************************************************************************** */

    // Copy Assignament
    NodeLnk& operator=(const NodeLnk&);

    // Move Assignament
    NodeLnk& operator=(NodeLnk&&) noexcept;

    /* ************************************************************************** */    

    // Specific member functions
    inline virtual Data& Element() noexcept override { return elem; }
    inline virtual const Data& Element() const noexcept override { return elem; }

    inline virtual bool IsLeaf() const noexcept override { return (!(HasLeftChild() || HasRightChild())); }; 
    
    inline virtual bool HasLeftChild() const noexcept override { return left!=nullptr; }
    inline virtual bool HasRightChild() const noexcept override { return right!=nullptr; }

    virtual NodeLnk& RightChild() override; // Must throw std::length_error when empty
    virtual const NodeLnk& RightChild() const override; // Must throw std::length_error when empty
    virtual NodeLnk& LeftChild() override; // Must throw std::length_error when empty
    virtual const NodeLnk& LeftChild() const override; // Must throw std::length_error when empty

  };

  NodeLnk * root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>&);  // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data>&&) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept; 

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk() { delete root; }; 

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&); 

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeLnk& btl) const noexcept { return BinaryTree<Data>::operator==(btl); };
  inline bool operator!=(const BinaryTreeLnk& btl) const noexcept { return !(operator==(btl)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  inline virtual const NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  inline virtual NodeLnk& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
