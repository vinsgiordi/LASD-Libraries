
namespace lasd {

/* ************************************************************************** */

// Specific constructors - Vector
template <typename Data>
Vector<Data>::Vector(const unsigned long newSize) {
   size = newSize;
   elements = new Data[size]();
}

template <typename Data>
inline Vector<Data>::Vector(const TraversableContainer<Data>& tc) : Vector(tc.Size()) {
   unsigned long i = 0;
   tc.Traverse(
      [this, &i](const Data& newData) {
         elements[i++] = newData;
      }
   );
}

template <typename Data>
inline Vector<Data>::Vector(MappableContainer<Data>&& mc) : Vector(mc.Size()) {
   unsigned long i = 0;
   mc.Map(
      [this, &i](Data& newData) {
         std::swap(elements[i++], newData);
      }
   );
}

/* ************************************************************************** */

// Copy constructor - Vector
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
   size = vec.size;
   elements = new Data[size];
   std::copy(vec.elements, vec.elements + size, elements);
}

// Move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
   std::swap(size, vec.size);
   std::swap(elements, vec.elements);
}

/* ************************************************************************** */

// Copy assignment - Vector
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
   Vector<Data> tmp {vec};
   std::swap(tmp, *this);
   return *this;
}

// Move assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
   std::swap(size, vec.size);
   std::swap(elements, vec.elements);
   return *this;
}

/* ************************************************************************** */

// Comparison operators - Vector
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
   if (size == vec.size) {
      for (unsigned long i = 0; i < size; i++) {
         if (elements[i] != vec[i]) {
            return false;
         }
      }
      return true;
   }
   else {
      return false;
   }
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector& vec) const noexcept {
   return !(*this == vec);
}

/* ************************************************************************** */

// Specific member function (ClearableContainer)
template <typename Data>
void Vector<Data>::Clear() {
   delete[] elements;
   elements = nullptr;
   size = 0;
}

/* ************************************************************************** */

// Specific member function (ResizableContainer)
template <typename Data>
void Vector<Data>::Resize(unsigned long newSize) {
   if (newSize == 0) {
      Clear();
   } else if (size != newSize) {
      Data* temp = new Data[newSize] {};
      const unsigned long minSize = (size < newSize) ? size : newSize;
      std::copy(elements, elements + minSize, temp);
      delete[] elements;
      elements = temp;
      size = newSize;
   }
}

/* ************************************************************************** */

// Specific memebr function - Vector (LinearContainer)
template <typename Data>
const Data& Vector<Data>::operator[](unsigned long i) const {
   if (i < size) {
      return elements[i];
   }
   else {
      throw std::out_of_range("L'indice supera la dimensione corrente");
   }
}

template <typename Data>
inline Data& Vector<Data>::operator[](unsigned long i) {
   if (i < size) {
      return elements[i];
   }
   else {
      throw std::out_of_range("L'indice supera la dimensione corrente");
   }
}

template <typename Data>
inline const Data& Vector<Data>::Front() const {
   if (size != 0) {
      return elements[0];
   }
   else {
      throw std::length_error("Vettore vuoto");
   }
}

template <typename Data>
inline Data& Vector<Data>::Front() {
   if ( size != 0) {
      return elements[0];
   }
   else {
      throw std::length_error("Vettore vuoto");
   }
}

template <typename Data>
inline const Data& Vector<Data>::Back() const {
   if (size != 0) {
      return elements[size - 1];
   }
   else {
      throw std::length_error("Vettore vuoto");
   }
}

template <typename Data>
inline Data& Vector<Data>::Back() {
   if (size != 0) {
      return elements[size - 1];
   }
   else {
      throw std::length_error("Vettore vuoto");
   }    
}

/* ************************************************************************** */

// Copy assignment - SortableVector
template <typename Data>
inline SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vec) {
   Vector<Data>::operator=(vec);
   return *this;
}

// Move assignment
template <typename Data>
inline SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept {
   Vector<Data>::operator=(std::move(vec));
   return *this;
}

/* ************************************************************************** */

}
