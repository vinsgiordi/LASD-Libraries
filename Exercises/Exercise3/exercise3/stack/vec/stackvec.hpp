
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

#define SIZE 16

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec: virtual public Stack<Data>, virtual protected Vector<Data> {

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::elements;

  unsigned long i{0};

  // ...

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  explicit StackVec(const TraversableContainer<Data>&); // A stack obtained from a TraversableContainer
  explicit StackVec(MappableContainer<Data>&&); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  explicit StackVec(const StackVec&);

  // Move constructor
  explicit StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline StackVec& operator=(const StackVec&);

  // Move assignment
  inline StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackVec&) const noexcept;
  inline bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline void Pop() override; // Override Stack member (must throw std::length_error when empty)
  inline Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  inline void Push(const Data&) override; // Override Stack member (copy of the value)
  inline void Push(Data&&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override { return i == 0; } // Override Container member

  inline unsigned long Size() const noexcept override { return i; } // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override;
  inline void Resize(unsigned long sres) override;

protected:

  // Auxiliary member functions, if necessary!

  /* ************************************************************************ */

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
