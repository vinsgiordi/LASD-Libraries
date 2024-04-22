
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

#define SIZE 16

/* ************************************************************************** */

template <typename Data>
class QueueVec: virtual public Queue<Data>, virtual protected Vector<Data> {

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::elements;

  unsigned long head{0}, tail{0}, realSize{0};

public:

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  explicit QueueVec(const TraversableContainer<Data>&);// A stack obtained from a TraversableContainer
  explicit QueueVec(MappableContainer<Data>&&); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  explicit QueueVec(const QueueVec&);

  // Move constructor
  explicit QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueVec& operator=(const QueueVec&);

  // Move assignment
  inline QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  inline bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  inline Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override; // Override Container member

  unsigned long Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override; // Override ClearableContainer member
  void Resize(unsigned long) override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
