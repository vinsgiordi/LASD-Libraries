
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {    // Must extend MutableBinaryTree<Data>

private:

protected:

  using Container::size;

  using typename BinaryTree<Data>::Node;

  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

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
  BinaryTreeLnk() = default;  // BinaryTreeLnk() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>&);  // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data>&&) noexcept; // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);  // BinaryTreeLnk(argument) specifiers;

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;  // BinaryTreeLnk(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk() { delete root; };  // ~BinaryTreeLnk() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&); // type operator=(argument) specifiers;

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept; // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeLnk& btl) const noexcept { return BinaryTree<Data>::operator==(btl); };  // type operator==(argument) specifiers;
  inline bool operator!=(const BinaryTreeLnk& btl) const noexcept { return !(operator==(btl)); }; // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  inline virtual const NodeLnk& Root() const override;  // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  inline virtual NodeLnk& Root() override;  // type Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override; // type Clear() specifiers; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
