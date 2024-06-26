
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr: virtual public HashTable<Data> {

private:

  static constexpr unsigned long  MIN_SIZE = 128;
  static constexpr unsigned long  MAX_SIZE = 2000000;

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::hash;
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::distA;
  using HashTable<Data>::distB;
  using HashTable<Data>::generator;
  using HashTable<Data>::tableSize;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::Insert;
  using HashTable<Data>::InsertAll;

  double capacity = 0;
  Vector<Data> table;
  Vector<char> statusVec;

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(unsigned long); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data>&); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(unsigned long, const TraversableContainer<Data>&); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data>&&); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(unsigned long, MappableContainer<Data>&&); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data>&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr<Data>&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data>&) const noexcept;
  inline bool operator!=(const HashTableOpnAdr<Data>& htopn) const noexcept { return !(operator==(htopn)); };

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  virtual void Resize(unsigned long) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  virtual void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  virtual unsigned long HashKey(const Data&, unsigned long) const noexcept;
  virtual unsigned long Find(const Data&, unsigned long) const noexcept;
  virtual unsigned long FindEmpty(const Data&, unsigned long) const noexcept;
  virtual bool Remove(const Data&, unsigned long);

  unsigned long FindNext2Pow(unsigned long) const noexcept;
  bool IsResizable(unsigned long) const noexcept;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
