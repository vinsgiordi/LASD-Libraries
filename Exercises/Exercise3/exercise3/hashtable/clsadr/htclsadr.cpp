
namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    table = new BST<Data>[tableSize] {};
}

/* ************************************************************************** */

// Specific constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long siz) {
    if(siz < 127) {
        siz = MIN_TABLESIZE;
    }

    if(siz >= 10000) {
        siz = MAX_TABLESIZE;
    }

    if(siz != MIN_TABLESIZE && siz != MAX_TABLESIZE) {
        siz = FindNextPrime(siz);
    }

    tableSize = siz;
    table = new BST<Data>[tableSize] {};
}

/* ************************************************************************** */

// Specific constructor from TraversableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& tc) : HashTableClsAdr() {
    InsertAll(tc);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long siz, const TraversableContainer<Data>& tc) : HashTableClsAdr(siz) {
    InsertAll(tc);
}

/* ************************************************************************** */

// Specific constructor from MappableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& mc) : HashTableClsAdr() {
    InsertAll(std::move(mc));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long siz, MappableContainer<Data>&& mc) : HashTableClsAdr(siz) {
    InsertAll(std::move(mc));
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& ht) : HashTable<Data>(ht) {
    table = new BST<Data>[tableSize] {};
    std::copy(ht.table, ht.table + tableSize, table); // copy all elements (start, end, destination)
}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& ht) noexcept : HashTable<Data>(std::move(ht)) {
    std::swap(table, ht.table);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
    delete[] table;
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& ht) {
    HashTableClsAdr<Data>* tmp = new HashTableClsAdr<Data>(ht);
    std::swap(*this, *tmp);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& ht) noexcept {
    std::swap(table, ht.table);
    std::swap(size, ht.size);
    std::swap(a, ht.a);
    std::swap(b, ht.b);
    std::swap(tableSize, ht.tableSize);
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>&  ht) const noexcept {
    if(size == ht.size) {
        for(unsigned long i = 0; i < tableSize; i++) {
            if(table[i].Size() != 0) {
                BTInOrderIterator<Data> it(table[i]);
                
                while(!(it.Terminated())) {
                    if(!(ht.Exists(it.operator*()))) {
                        return false;
                    }
                    it.operator++();
                }
            }
        }
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>&  ht) const noexcept {
    return !(*this == ht);
}

/* ************************************************************************** */

// Specific member functions from DictionaryContainer
template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) {
    if(table[HashKey(data)].Insert(data)) {
        ++size;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) noexcept {
    if(table[HashKey(data)].Insert(std::move(data))) {
        ++size;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& data) {
    if(table[HashKey(data)].Remove(data)) {
        --size;
        return true;
    }
    return false;
}

/* ************************************************************************** */

// Specific member functions from TestableContainer
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    return table[HashKey(data)].Exists(data);
};

/* ************************************************************************** */

// Specific member functions from ResizableContainer
template <typename Data>
void HashTableClsAdr<Data>::Resize(unsigned long newSize) {
    HashTableClsAdr<Data>* tmp = new HashTableClsAdr<Data>(newSize);
    for(unsigned long i = 0; i < tableSize; ++i) {
        if(table[i].Size() != 0) {
            BTInOrderIterator<Data> it(table[i]);

            while(!(it.Terminated())) {
                Data data = it.operator*();
                tmp->Insert(data);
                it.operator++();
            }
        }
    }
    std::swap(*this, *tmp);
    delete tmp;
}

/* ************************************************************************** */

// Specific member functions form ClearableContainer
template <typename Data>
void HashTableClsAdr<Data>::Clear() {
    delete[] table;
    table = new BST<Data>[tableSize] {};
    size = 0;
}

/* ************************************************************************** */

// Auxiliary member functions
template <typename Data>
unsigned long HashTableClsAdr<Data>::FindNextPrime(unsigned long value) const noexcept {
    for(ulong i = 2; i <= value / 2; ++i) {
        if(value % i == 0) {
            value += 1;
            i = 2;
        }
    }
    return value;
}

/* ************************************************************************** */

}
