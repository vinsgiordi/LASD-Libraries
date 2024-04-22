
namespace lasd {

/* ************************************************************************** */

// Copy Assignment  - StakList
template <typename Data>
inline StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stack) {
    List<Data>::operator=(stack);
    return *this;
}

// Move Assigment 
template <typename Data>
inline StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stack) noexcept {
    List<Data>::operator=(std::move(stack));
    return *this;
}

/* ************************************************************************** */

// Comparison Operators
template <typename Data>
inline bool StackLst<Data>::operator==(const StackLst<Data>& stack) const noexcept {
    return List<Data>::operator==(stack);
}

template <typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& stack) const noexcept {
    return List<Data>::operator!=(stack);
}

/* ************************************************************************** */

// Specific member functions - Stack 
template <typename Data>
inline const Data& StackLst<Data>::Top() const {
    return List<Data>::Front();
}

template <typename Data>
inline Data& StackLst<Data>::Top() {
    return List<Data>::Front();
}

template <typename Data>
inline void StackLst<Data>::Pop() {
    List<Data>::RemoveFromFront();
}

template <typename Data>
inline Data StackLst<Data>::TopNPop() {
    return List<Data>::FrontNRemove();
}

template <typename Data>
inline void StackLst<Data>::Push(const Data& data) {
    List<Data>::InsertAtFront(data);
}

template <typename Data>
inline void StackLst<Data>::Push(Data&& data) noexcept {
    List<Data>::InsertAtFront(std::move(data));
}

/* ************************************************************************** */

}
