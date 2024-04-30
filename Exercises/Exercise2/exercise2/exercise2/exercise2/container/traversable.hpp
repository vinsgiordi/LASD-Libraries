
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer: virtual public TestableContainer<Data>{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer& operator=(const TraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  TraversableContainer& operator=(TraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const TraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  inline Accumulator Fold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer: virtual public TraversableContainer<Data>{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const PreOrderTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(const TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  inline Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override;  // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer: public virtual TraversableContainer<Data>{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderTraversableContainer& operator=(PostOrderTraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const PostOrderTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  inline Accumulator PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer : public virtual TraversableContainer<Data> {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderTraversableContainer& operator=(const InOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  InOrderTraversableContainer& operator=(InOrderTraversableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const InOrderTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void InOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  inline Accumulator InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer: virtual public TraversableContainer<Data> {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthTraversableContainer& operator=(const BreadthTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BreadthTraversableContainer& operator=(BreadthTraversableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const BreadthTraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void BreadthTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  inline Accumulator BreadthFold(FoldFun<Accumulator> fun, Accumulator acc) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
