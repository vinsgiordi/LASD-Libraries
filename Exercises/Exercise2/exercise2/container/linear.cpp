
namespace lasd {

/* ************************************************************************** */

// Comparison operators
template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& lc) const noexcept {
    if (size != lc.size) {
        return false;
    }

    for (unsigned long i = 0; i < size; i++) {
        if ((*this)[i] != lc[i]) {
            return false;
        }
    }
    return true;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& lc) const noexcept {
    return !(*this == lc);
}

/* ************************************************************************** */

// Specific member function (LinearContainer)
template <typename Data>
inline const Data& LinearContainer<Data>::Front() const {
    if(size == 0){
        throw std::length_error("Array vuoto");
    }
    else {
        return operator[](0);
    }
}

template <typename Data>
inline Data& LinearContainer<Data>::Front() {
    if(size == 0){
        throw std::length_error("Array vuoto");
    }
    else {
        return operator[](0);
    }
}

template <typename Data>
inline const Data& LinearContainer<Data>::Back() const { 
    if(size == 0) {
        throw std::length_error("Array vuoto");
    }
    else {
        return operator[](size - 1);
    }
}

template <class Data>
inline Data& LinearContainer<Data>::Back() {
    if(size == 0) {
        throw std::length_error("Array vuoto");
    }
    else {
        return operator[](size - 1);
    }
}

/* ************************************************************************** */

// Specific member function (inherited from TraversableContainer)
template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderTraversableContainer)
template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(const TraverseFun fun) const {
    for (unsigned long i = 0; i < size; ++i) {
        fun(operator[](i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderTraversableContainer)
template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(const TraverseFun fun) const {
    unsigned long i = size;
    
    while (i > 0) {
     fun(operator[](--i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)
template <typename Data>
inline void LinearContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderMappableContainer)
template <typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFun fun) {
    for (unsigned long i = 0; i < size; i++) {
        fun(operator[](i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderMappableContainer)
template <typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFun fun) {
    unsigned long i = size;
    
    while (i > 0) {
        fun(operator[](--i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from SortableLinearContainer)
template <typename Data>
inline void SortableLinearContainer<Data>::Sort() noexcept {
    QuickSort(0, size - 1);
}

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(unsigned long p, unsigned long r) noexcept {
    if (p < r) {
        unsigned long q = Partition(p, r);
        QuickSort(p, q);
        QuickSort(q + 1, r);
    }
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::Partition(unsigned long p, unsigned long r) noexcept {
    Data value = operator[](p);
    unsigned long i = p - 1;
    unsigned long j = r + 1;

    do {
        do {j--;} 
        while (value < operator[](j));
        do {i++;}
        while(value > operator[](i));
        if (i < j) { 
            std::swap(operator[](i), operator[](j));
        }
    } while (i < j);

    return j;
}

/* ************************************************************************** */
}
 