
namespace lasd
{

  /* ************************************************************************** */

  // Copy constructor from Different DataStructures
  template <typename Data>
  QueueLst<Data>::QueueLst(const TraversableContainer<Data> &tc) : List<Data>::List(tc) {}

  // Move constructor from Different DataStructures
  template <typename Data>
  QueueLst<Data>::QueueLst(MappableContainer<Data> &&mc) : List<Data>::List(std::move(mc)) {}

  /* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const QueueLst<Data> &queue) : List<Data>::List(queue) {}

  // Move constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(QueueLst<Data> &&queue) noexcept : List<Data>::List(std::move(queue)) {}

  /* ************************************************************************** */

  // Copy assignment
  template <typename Data>
  inline QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &queue)
  {
    List<Data>::operator=(queue);
    return *this;
  }

  // Move assignment
  template <typename Data>
  inline QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&queue) noexcept
  {
    List<Data>::operator=(std::move(queue));
    return *this;
  }

  /* ************************************************************************** */

  // Comparison operators
  template <typename Data>
  inline bool QueueLst<Data>::operator==(const QueueLst<Data> &queue) const noexcept
  {
    return List<Data>::operator==(queue);
  }

  template <typename Data>
  inline bool QueueLst<Data>::operator!=(const QueueLst<Data> &queue) const noexcept
  {
    return !(*this == queue);
  }

  /* ************************************************************************** */

  // Specific member functionsì
  template <typename Data>
  inline Data &QueueLst<Data>::Head()
  {
    if (!size)
    {
      throw std::length_error("The queue is empty");
    }

    return List<Data>::Front();
  }

  template <typename Data>
  inline const Data &QueueLst<Data>::Head() const
  {
    if (!size)
    {
      throw std::length_error("The queue is empty");
    }

    return List<Data>::Front();
  }

  template <typename Data>
  inline void QueueLst<Data>::Dequeue()
  {
    if (!size)
    {
      throw std::length_error("The queue is empty");
    }

    return List<Data>::RemoveFromFront();
  }

  template <typename Data>
  inline Data QueueLst<Data>::HeadNDequeue()
  {
    if (!size)
    {
      throw std::length_error("The queue is empty");
    }

    return List<Data>::FrontNRemove();
  }

  template <typename Data>
  inline void QueueLst<Data>::Enqueue(const Data &data)
  {
    return List<Data>::InsertAtBack(data);
  }

  template <typename Data>
  inline void QueueLst<Data>::Enqueue(Data &&data)
  {
    return List<Data>::InsertAtBack(std::move(data));
  }

  /* ************************************************************************** */

} // namespace lasd