
namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>::Vector(SIZE) {}

// Copy constructor from Different DataStructures
template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data> &tc)
    : Vector<Data>::Vector(tc), i(tc.Size()) {
  if (size < SIZE)
    Resize(SIZE);
}

// Move constructor from Different DataStructures
template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data> &&mc)
    : Vector<Data>::Vector(std::move(mc)), i(mc.Size()) {
  if (size < SIZE)
    Resize(SIZE);
}

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& stack)
    : Vector<Data>::Vector(stack), i(stack.i) {}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stack) noexcept
    : Vector<Data>::Vector(std::move(stack)) {
  std::swap(i, stack.i);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
inline StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> &stack) {
  Vector<Data>::operator=(stack);
  i = stack.i;
  return *this;
}

// Move assignment
template <typename Data>
inline StackVec<Data> &StackVec<Data>::operator=(StackVec<Data> &&stack) noexcept {
  Vector<Data>::operator=(std::move(stack));
  std::swap(i, stack.i);
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
inline bool StackVec<Data>::operator==(const StackVec<Data> &stack) const noexcept {
  if (i != stack.i)
    return false;

  for (unsigned long index = 0; index < i; index++) {
    if (elements[index] != stack[index]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data> &stack) const noexcept {
  return !(*this == stack);
}

/* ************************************************************************** */

// Specific member functions
template <typename Data> 
inline const Data &StackVec<Data>::Top() const {
  if (!i)
    throw std::length_error("The stack is empty");
  return elements[i - 1];
}

template <typename Data>
inline Data &StackVec<Data>::Top() {
  if (!i)
    throw std::length_error("The stack is empty");
  return elements[i - 1];
}

template <typename Data>
inline void StackVec<Data>::Pop() {
  if (!i)
    throw std::length_error("The stack is empty");

  if (--i < size / 4)
    Resize(size / 2);
}

template <typename Data>
inline Data StackVec<Data>::TopNPop() {
  Data top{Top()};
  Pop();
  return top;
}

template <typename Data>
void StackVec<Data>::Push(const Data &data) {
  if (i == size)
    Resize(size * 2);
  elements[i++] = data;
}

template <typename Data>
void StackVec<Data>::Push(Data &&data) {
  if (i == size)
    Resize(size * 2);
  elements[i++] = std::move(data);
}

template <typename Data>
inline void StackVec<Data>::Clear() {
  Resize(SIZE);
  i = 0;
}

template <typename Data>
inline void StackVec<Data>::Resize(unsigned long stack) {
  if (stack >= SIZE)
    Vector<Data>::Resize(stack);
}

/* ************************************************************************** */

} // namespace lasd