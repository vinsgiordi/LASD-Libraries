
namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    tableSize = MIN_SIZE;
    size = 0;

    a = 2*(distA(generator)) + 1;
    b = 2*(distB(generator));

    table.Resize(tableSize);
    statusVec.Resize(tableSize);

    for(unsigned long i = 0; i < tableSize; i++) {
        statusVec[i] = 'E'; // Empty, Full, Removed
    }
    capacity = (static_cast<double>(size)/static_cast<double>(tableSize))*100;
}

/* ************************************************************************** */

// Specific constructor 
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long val) {
    size = 0;

    a = 2*(distA(generator)) + 1;
    b = 2*(distB(generator));

    tableSize = FindNext2Pow(val);
    table.Resize(tableSize);
    statusVec.Resize(tableSize);

    for(unsigned long i = 0; i < tableSize; i++) {
        statusVec[i] = 'E'; // Empty, Full, Removed
    }
    capacity = (static_cast<double>(size)/static_cast<double>(tableSize))*100;
}

/* ************************************************************************** */

// Specific constructor from TraversableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& tc) : HashTableOpnAdr() {
    InsertAll(tc);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long val, const TraversableContainer<Data>& tc) : HashTableOpnAdr(val) {
    InsertAll(tc);
}

/* ************************************************************************** */

// Specific constructor from MappableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& mc) : HashTableOpnAdr() {
    InsertAlll(std::move(mc));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long val, MappableContainer<Data>&& mc) : HashTableOpnAdr(val) {
    InsertAlll(std::move(mc));
}

/* ************************************************************************** */

// Copy constructor 
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& ht) {
    size = ht.size;
    tableSize = ht.tableSize;
    a = ht.a;
    b = ht.b;
    table = ht.table;
    statusVec = ht.statusVec;
    capacity = ht.capacity;
}

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& ht) noexcept {
    std::swap(size, ht.size);
    std::swap(tableSize, ht.tableSize);
    std::swap(a, ht.a);
    std::swap(b, ht.b);
    std::swap(table, ht.table);
    std::swap(statusVec, ht.statusVec);
    std::swap(capacity, ht.capacity);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& ht) {
    HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr(ht);
    std::swap(*this, *tmp);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& ht) noexcept {
    std::swap(size, ht.size);
    std::swap(tableSize, ht.tableSize);
    std::swap(a, ht.a);
    std::swap(b, ht.b);
    std::swap(table, ht.table);
    std::swap(statusVec, ht.statusVec);
    std::swap(capacity, ht.capacity);
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& ht) const noexcept {
    if (size == ht.size) {
        for (unsigned long i = 0; i < tableSize; i++) {
            if (statusVec[i] == 'F') { // Empty, Full, Removed
                if(!(ht.Exists(table[i]))) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

/* ************************************************************************** */

// Specific member functions from DictionaryContainer
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    capacity = (static_cast<double>(size)/static_cast<double>(tableSize)) * 100;

    if(capacity > 75) {
        Resize(2 * tableSize + 1);
    }

    if(!Exists(data)) {
        unsigned long index = FindEmpty(data, 0);
        if(index < tableSize) {
            unsigned long pos = HashKey(data, index);
            if(statusVec[pos] == 'E' || statusVec[pos] == 'R') {
                table[pos] = data;
                statusVec[pos] = 'F';
                size++;
                return true;
            }
        }
    }
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    capacity = (static_cast<double>(size)/static_cast<double>(tableSize)) * 100;
    if(capacity > 75) {
        Resize(2 * tableSize + 1);
    }

    if(!Exists(data)) {
        unsigned long index = FindEmpty(data, 0);
        if(index < tableSize) {
            unsigned long pos = HashKey(data, index);
            if(statusVec[pos] == 'E' || statusVec[pos] == 'R') {
                table[pos] = std::move(data);
                statusVec[pos] = 'F';
                size++;
                return true;
            }
        }
    }
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    capacity = (static_cast<double>(size)/static_cast<double>(tableSize)) * 100;
    bool res = Remove(data, 0);
    if(capacity < 10) {
        Resize((tableSize / 2) - 1);
    }
    return res;
}

/* ************************************************************************** */

// Specific member functions from TestableContainer
template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    if(size > 0) {
        unsigned long index = Find(data, 0);
        if(index < tableSize) {
            unsigned long pos = HashKey(data, index);
            if(statusVec[pos] == 'F' && table[pos] == data) {
                return true;
            }
        }
    }
    return false;
}

/* ************************************************************************** */

// Specific member functions from ResizableContainer
template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long siz) {
    unsigned long newSize = siz;
    if(!IsResizable(siz)) {
        return;
    }

    HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr<Data>(newSize);
    for(unsigned long i = 0; i < tableSize; i++) {
        if(statusVec[i] == 'F') {
            tmp->Insert(table[i]);
        }
    }
    std::swap(*this, *tmp);
    delete tmp;
}

/* ************************************************************************** */

// Specific member functions from ClearableContainer
template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    tableSize = MIN_SIZE;
    size = 0;
    table.Clear();
    table.Resize(tableSize);
    statusVec.Resize(tableSize);

    for(unsigned long i = 0; i < tableSize; i++) {
        statusVec[i] = 'E';
    }
}

/* ************************************************************************** */

// Auxiliary member functions
template <typename Data>
unsigned long HashTableOpnAdr<Data>::HashKey(const Data& data, unsigned long index) const noexcept { 
    unsigned long key = hash(data);
    return ((HashKey(key) + ((index * index) + index) / 2) % tableSize); // Quadratic probing
}

template <typename Data>
unsigned long HashTableOpnAdr<Data>::Find(const Data& data, unsigned long index) const noexcept {
    unsigned long start = HashKey(data, index);
    ulong collision = 0;
    while(index < tableSize) {
        if(table[start] == data) {
            return index;
        }
        if(statusVec[start] == 'E') {
            return tableSize;
        }
        collision++;
        index++;
        start = HashKey(data, index);
    }
    return index;
}

template <typename Data>
unsigned long HashTableOpnAdr<Data>::FindEmpty(const Data& data, unsigned long index) const noexcept {
    unsigned long start = HashKey(data, index);
    ulong collision = 0;
    while(index < tableSize) {
        if(statusVec[start] == 'E' || statusVec[start] == 'R') {
            return index;
        }
        collision++;
        index++;
        start = HashKey(data, index);
    }
    return index;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data, unsigned long index) {
    if(size > 0) {
        unsigned long idx = Find(data, index);
        if(idx < tableSize) {
            unsigned long pos = HashKey(data, idx);
            if(statusVec[pos] == 'F' && table[pos] == data) {
                statusVec[pos] = 'R';
                size--;
                return true;
            }
        }
    }
    return false;
}

template <typename Data>
unsigned long HashTableOpnAdr<Data>::FindNext2Pow(unsigned long siz) const noexcept {
    unsigned long newSize = MIN_SIZE;
    while(newSize < siz) {
        if(newSize >= MAX_SIZE) {
            break;
        }
        newSize = newSize << 1;
    }
    return newSize;
}


template <typename Data>
bool HashTableOpnAdr<Data>::IsResizable(unsigned long siz) const noexcept {
    if(size > tableSize) {
        return true;
    } else {
        if(siz == tableSize) {
            return false;
        }
        ulong cap = (static_cast<double>(size)/static_cast<double>(size)) * 100;
        if(cap < 75) {
            return true;
        }
        return false;
    }
}

/* ************************************************************************** */

}
