

namespace lasd {

/* ************************************************************************** */

// Specific member function (PreOrderMappableContainer)
template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (PostOrderMappableContainer)
template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun fun) {
   PostOrderMap(fun); 
}

/* ************************************************************************** */

// Specific member function (InOrderMappableContainer)

/* ************************************************************************** */

// Specific member function (BreadthMappableContainer)

/* ************************************************************************** */

}
