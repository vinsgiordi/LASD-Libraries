
namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>::Vector(SIZE) {}

// Copy constructor from Different DataStructures
template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data>& tc)
    : Vector<Data>::Vector(tc), tail(tc.Size()), realSize(tc.Size()) {
  if (size < SIZE)
    Resize(SIZE);
}

// Move constructor from Different DataStructures
template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data>&& mc)
    : Vector<Data>::Vector(std::move(mc)), tail(mc.Size()), realSize(mc.Size()) {
  if (size < SIZE)
    Resize(SIZE);
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& queue)
    : Vector<Data>::Vector(queue), head(queue.head), tail(queue.tail), realSize(queue.realSize) {}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept
    : Vector<Data>::Vector(std::move(queue)) {
  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  std::swap(realSize, queue.realSize);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
inline QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec<Data>& queue) {
  Vector<Data>::operator=(queue);

  head = queue.head;
  tail = queue.tail;
  realSize = queue.realSize;

  return *this;
}

// Move assignment
template <typename Data>
inline QueueVec<Data> &QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept {
  Vector<Data>::operator=(std::move(queue));

  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  std::swap(realSize, queue.realSize);

  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
inline bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept {
  if (queue.realSize != realSize)
    return false;

  for (unsigned long i = 0; i < realSize; i++)
    if (elements[(head + i) % size] != queue[(queue.head + i) % queue.size])
      return false;

  return true;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept {
  return !(*this == queue);
}

/* ************************************************************************** */

// Specific member functions
template <typename Data>
inline const Data &QueueVec<Data>::Head() const {
  if (!realSize)
    throw std::length_error("The queue is empty");
  return elements[head];
};

template <typename Data>
inline Data &QueueVec<Data>::Head() {
  if (!realSize)
    throw std::length_error("The queue is empty");
  return elements[head];
};

template <typename Data>
inline void QueueVec<Data>::Dequeue() {
  if (!realSize)
    throw std::length_error("The queue is empty");

  head = (head + 1) % size;

  if (--realSize == size / 4)
    Resize(size / 2);
}

template <typename Data>
inline Data QueueVec<Data>::HeadNDequeue() {
  Data headEl = Head();
  Dequeue();
  return headEl;
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& data) {
  if (realSize == size)
    Resize(size * 2);

  elements[tail] = data;
  tail = (tail + 1) % size;
  ++realSize;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& data) {
  if (realSize == size)
    Resize(size * 2);

  elements[tail] = std::move(data);
  tail = (tail + 1) % size;
  ++realSize;
}

template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {
  return realSize == 0;
}

template <typename Data>
inline unsigned long QueueVec<Data>::Size() const noexcept {
  return realSize;
}

template <typename Data> inline void QueueVec<Data>::Clear() {
  Resize(SIZE);
  tail = head = realSize = 0;
}

template <typename Data>
void QueueVec<Data>::Resize(unsigned long s) {
  if (s < SIZE || s == size)
    return;

  Data *temp{new Data[s]{}};
  for (unsigned long i{head}, j{0}; j < realSize; i = (i + 1) % size, ++j)
    temp[j] = elements[i];

  std::swap(elements, temp);
  delete[] temp;

  head = 0;
  tail = realSize;
  size = s;
}

/* ************************************************************************** */

} // namespace lasd