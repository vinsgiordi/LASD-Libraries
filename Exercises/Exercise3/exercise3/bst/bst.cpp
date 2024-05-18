#include "bst.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructor - TraversableContainer
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data>& tc){
  tc.Traverse(
    [this](const Data& data){
        Insert(data);
    }
  );
}

/* ************************************************************************** */

// Specific constructor - MappableContainer
template <typename Data>
BST<Data>::BST(MappableContainer<Data>&& map) noexcept {
  map.Map(
    [this](Data& data){
        Insert(std::move(data));
    }
  );
}

/* ************************************************************************** */

// Copy constructor - BST
template<typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst) {}

// Move constructor
template<typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) {}

/* ************************************************************************** */

// Copy assignment - BST
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst){
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

/* ************************************************************************** */

// Comparison operator - BST
template <typename Data>
bool BST<Data>::operator==(const BST& bst) const noexcept {
  if (size == bst.Size()) {
    BTInOrderIterator<Data> iter1(*this);
    BTInOrderIterator<Data> iter2(bst);
    for (; !iter1.Terminated(); ++iter1, ++iter2) {
      if((*iter1)!=(*iter2))
        return false;
    }
    return true;
  }
  return false;
}

/* ************************************************************************** */

// Specific member functions - BST
template<typename Data>
const Data& BST<Data>::Min() const {
  if (root != nullptr)
    return FindPointerToMin(root)->elem;
  else
    throw std::length_error("Empty tree");
}

template <typename Data>
Data BST<Data>::MinNRemove(){
  if (root != nullptr)
    return DataNDelete(DetachMin(root));
  else
    throw std::length_error("Empty tree");
}

template<typename Data>
void BST<Data>::RemoveMin(){
  if (root != nullptr)
    delete DetachMin(root);
  else
    throw std::length_error("Empty tree");
}

/* ************************************************************************** */

template <typename Data>
const Data& BST<Data>::Max()const{
  if (root != nullptr)
    return FindPointerToMax(root)->elem;
  else
    throw std::length_error("Empty tree");
}

template <typename Data>
Data BST<Data>::MaxNRemove(){
  if (root != nullptr)
    return DataNDelete(DetachMax(root));
  else
    throw std::length_error("Empty tree");
}

template<typename Data>
void BST<Data>::RemoveMax(){
  if (root != nullptr)
    delete DetachMax(root);
  else
    throw std::length_error("L'albero è vuoto in RemoveMax()");
}

/* ************************************************************************** */

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
  NodeLnk* const* ptr=&FindPointerToPredecessor(root,data);
  if (ptr != nullptr)
    return (*ptr)->elem;
  else
    throw std::length_error("Error: predecessor not found");
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data){
  NodeLnk** ptr=&FindPointerToPredecessor(root,data);
  if (ptr != nullptr)
    return DataNDelete(Detach(*ptr));
  else
    throw std::length_error("Error: predecessor not found");
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data){
  NodeLnk** ptr=&FindPointerToPredecessor(root,data);
  if (ptr != nullptr)
    delete Detach(*ptr);
  else
    throw std::length_error("Error: predecessor not found");
}

/* ************************************************************************** */

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
  NodeLnk* const* ptr=&FindPointerToSuccessor(root,data);
  if(ptr !=nullptr)
    return (*ptr)->elem;
  else
    throw std::length_error("Error: successor not found");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data){
  NodeLnk** ptr=&FindPointerToSuccessor(root,data);
  if (ptr != nullptr)
    return DataNDelete(Detach(*ptr));
  else
    throw std::length_error("Error: successor not found");
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data){
  NodeLnk **ptr = &FindPointerToSuccessor(root, data);
  if (ptr != nullptr)
    delete Detach(*ptr);
  else
    throw std::length_error("Error: successor not found");
}

/* ************************************************************************** */

// Specific member functions - BST from DictionaryContainer
template <typename Data>
bool BST<Data>::Insert(const Data& data){
  NodeLnk*& ptr=FindPointerTo(root, data);
  if(ptr==nullptr){
    ptr=new NodeLnk(data);
    size++;
    return true;
  }
  return false;
}

template <typename Data>
bool BST<Data>::Insert(Data&& data){
  NodeLnk*& ptr=FindPointerTo(root, data);
  if(ptr==nullptr){
    ptr=new NodeLnk(std::move(data));
    size++;
    return true;
  }
  return false;
}

template <typename Data>
bool BST<Data>::Remove(const Data& data) {
  NodeLnk*& ptr=FindPointerTo(root, data);
  if(ptr!=nullptr){
    delete Detach(ptr);
    return true;
  }
  return false;
}
/* ************************************************************************** */

// Specific member function - BST from TestableContainer
template <typename Data>
bool BST<Data>::Exists(const Data& data) const noexcept {
  return (FindPointerTo(root, data) !=nullptr);
}

/* ************************************************************************** */

// Auxiliary function
template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node){
  Data data {};
  std::swap(data, node->elem);
  delete node;
  return data;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
  if (node != nullptr) {
    if (node->left == nullptr)
      return Skip2Right(node);
    else if (node->right == nullptr)
      return Skip2Left(node);
    else {
      NodeLnk *max = DetachMax(node->left);
      std::swap(node->elem, max->elem);
      return max;
    }
  }
  return nullptr;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
  return Skip2Right(FindPointerToMin(node));
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
  return Skip2Left(FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& node) noexcept {
  NodeLnk* left = nullptr;
  if (node != nullptr) {
    std::swap(left, node->left);
    std::swap(left, node);
    size--;
  }
  return left;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& node) noexcept {
  NodeLnk *right = nullptr;
  if (node != nullptr) {
    std::swap(right, node->right);
    std::swap(right, node);
    size--;
  }
  return right;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& node) const noexcept {
  NodeLnk* const* ptr=&node;
  NodeLnk* curr=node;
  if(curr!=nullptr)
    while(curr->left!=nullptr){
      ptr=&curr->left;
      curr=curr->left;
    }
  return *ptr;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& node) const noexcept {
  NodeLnk* const* ptr=&node;
  NodeLnk* curr=node;
  if(curr!=nullptr)
    while(curr->right!=nullptr){
      ptr=&curr->right;
      curr=curr->right;
    }
  return *ptr;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, Data data) const noexcept {
  NodeLnk *const *ptr = &node;
  NodeLnk *curr = node;

  while (curr != nullptr) {
    if (data > curr->elem) {
      ptr = &curr->right;
      curr = curr->right;
    }
    else if (data < curr->elem) {
      ptr = &curr->left;
      curr = curr->left;
    }
    else
      break;
  }
  return *ptr;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, Data data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node,data));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, Data data) const noexcept {
  NodeLnk *const *pred = nullptr;
  NodeLnk *const *curr = &node;
  while ((*curr) != nullptr && (*curr)->elem != data) {
    if ((*curr)->elem > data) {
      curr = &(*curr)->left;
    }
    else if ((*curr)->elem < data) {
      pred = curr;
      curr = &(*curr)->right;
    }
  }
  if ((*curr) != nullptr && (*curr)->left != nullptr)
    pred = &FindPointerToMax((*curr)->left);
  return *pred;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, Data data) const noexcept {
  typename BST<Data>::NodeLnk *const *succ = nullptr;
  typename BST<Data>::NodeLnk *const *curr = &node;
  while ((*curr) != nullptr && (*curr)->elem != data) {
    if ((*curr)->elem < data)
      curr = &(*curr)->right;
    else if ((*curr)->elem > data) {
      succ = curr;
      curr = &(*curr)->left;
    }
  }
  if ((*curr) != nullptr && (*curr)->right != nullptr)
    succ = &FindPointerToMin((*curr)->right);
  return *succ;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& node, Data data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node,data));
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& node, Data data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node,data));
}

/* ************************************************************************** */

};
