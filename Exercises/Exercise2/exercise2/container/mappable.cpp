

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
template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun fun) {
    InOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (BreadthMappableContainer)
template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun fun) {
    BreadthMap(fun);
}

/* ************************************************************************** */

}
