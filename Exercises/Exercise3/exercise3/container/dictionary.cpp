
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

// Specific member functions (DictionaryContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& tc) {
  bool insert = true;
  tc.Traverse(
    [this, &insert](const Data & data) {
      insert &= this->Insert(data);
    }
  );
  return insert;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& mc) {
  bool insert = true;
  mc.Map(
    [this, &insert](Data & data) {
      insert &= this->Insert(std::move(data));
    }
  );
  return insert;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& tc) {
  bool remove = true;
  tc.Traverse(
    [this, &remove](const Data& data) {
      remove &= this->Remove(data);
    }
  );
  return remove;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& tc) {
  bool some = false;
  tc.Traverse(
    [this, &some] (const Data & data) {
      some |= this->Insert(data);
    }
  );
  return some;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& mc) {
  bool some = false;
  mc.Map(
    [this, &some] (Data && data) {
      some |= this->Insert(std::move(data));
    }
  );
  return some;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& tc) {
  bool some = false;
  tc.Traverse(
    [this, &some] (const Data & data) {
      some |= this->Remove(data);
    }
  );
  return some;
}

/* ************************************************************************** */

}
