
namespace lasd {

/* ************************************************************************** */

// Auxiliary private member functions
template <typename Data>
void HashTableClsAdr<Data>::InitTable(unsigned long size)  {
    tableSize = size;
    if (tableSize == 0) {
        tableSize = MIN_TABLESIZE;
    }
    table = new BST<Data>[tableSize] {};
}

/* ************************************************************************** */

// Default constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    InitTable(MIN_TABLESIZE);
}

/* ************************************************************************** */

// Specific constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long siz) {
   if (siz < MIN_TABLESIZE) {
    siz = MIN_TABLESIZE;
   } else if (siz > MAX_TABLESIZE) {
    siz = MAX_TABLESIZE;
   } else {
    siz = FindNextPrime(siz);
   }
   InitTable(siz);
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
    InitTable(ht.tableSize);
    std::copy(ht.table, ht.table + tableSize, table);
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
   if (this != &ht) {
    HashTableClsAdr<Data>* tmp  = new HashTableClsAdr<Data>(ht);
    std::swap(*this, *tmp);
    delete tmp;
   }
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
   TransferData(tmp);
   std::swap(*this, *tmp);
   delete tmp;
}

/* ************************************************************************** */

// Specific member functions form ClearableContainer
template <typename Data>
void HashTableClsAdr<Data>::Clear() {
   delete[] table;
   InitTable(tableSize);
   size = 0;
}

/* ************************************************************************** */

// Auxiliary member functions
template <typename Data>
unsigned long HashTableClsAdr<Data>::FindNextPrime(unsigned long value) const noexcept {
   while(true) {
    bool isPrime = true;
    for (unsigned long i = 2; i * i <= value; ++i) {
        if(value % 1 == 0) {
            isPrime = false;
            break;
        }
    }
    if (isPrime) return value;
    ++value;
   }
}

template <typename Data>
void HashTableClsAdr<Data>::TransferData(HashTableClsAdr<Data>* newTable) {
    for (unsigned long i = 0; i < tableSize; ++i) {
        BTInOrderIterator<Data> it(table[i]);
        while (!it.Terminated()) {
            newTable->Insert(it.operator*());
            it.operator++();
        }
    }
}

/* ************************************************************************** */

}
