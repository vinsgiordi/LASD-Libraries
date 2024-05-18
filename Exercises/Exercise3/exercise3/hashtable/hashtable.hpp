
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  virtual unsigned long operator()(const Data) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable: virtual public ResizableContainer, virtual public DictionaryContainer<Data>{

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;
  
  unsigned long a = 1;
  unsigned long b = 0;
  static const unsigned long prime = 10000000000;

  std::default_random_engine generator = std::default_random_engine(std::random_device {}());
  std::uniform_int_distribution<unsigned long> distA = std::uniform_int_distribution<unsigned long>(1, prime - 1);
  std::uniform_int_distribution<unsigned long> distB = std::uniform_int_distribution<unsigned long>(0, prime - 1);

  static const Hashable<Data> hash;
  unsigned long tableSize = 127;

  /* ************************************************************************ */

  // Default constructor
  HashTable() {
    a = distA(generator);
    b = distB(generator);
  }

  /* ************************************************************************ */

  // Copy constructor
  HashTable(const HashTable& ht) {
    size = ht.size;
    a = ht.a;
    b = ht.b;
    tableSize = ht.tableSize;
  }

  // Move constructor
  HashTable(HashTable&& ht) noexcept {
    std::swap(size, ht.size);
    std::swap(a, ht.a);
    std::swap(b, ht.b);
    std::swap(tableSize, ht.tableSize);
  }

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  virtual unsigned long HashKey(const Data& data) const noexcept {
    return HashKey(hash(data));
  };

  virtual unsigned long HashKey(unsigned long key) const noexcept {
    return (((a * key + b) % prime) % tableSize);
  };

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
