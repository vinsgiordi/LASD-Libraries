
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */


namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  unsigned long size {0};

  /* ************************************************************************ */

  // Default constructor
  Container() = default;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container& operator=(Container&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  inline virtual bool Empty() const noexcept {
    return (size  == 0);
  }

  inline virtual unsigned long Size() const noexcept  {
    return size;
  }

};

/* ************************************************************************** */

class ClearableContainer: virtual public Container{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) noexcept = delete;  // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ClearableContainer&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer: virtual public ClearableContainer{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&) noexcept = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer& operator=(ResizableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResizableContainer&) const noexcept = delete;// Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(unsigned long) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override {
    Resize(0);
  }
  
};

/* ************************************************************************** */

}

#endif
