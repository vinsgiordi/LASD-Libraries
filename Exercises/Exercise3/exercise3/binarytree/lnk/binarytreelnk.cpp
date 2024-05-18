#include "binarytreelnk.hpp"

namespace lasd {

/* ************************************************************************** */

// Copy constructor - NodeLnk
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& node){
    elem = node.elem;

    if(node.left != nullptr) {
        left = new NodeLnk(*node.left);
    }
    else {
        left = nullptr;
    }

    if(node.right != nullptr) {
        right = new NodeLnk(*node.right);
    }
    else {
        right = nullptr;
    }
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& node) noexcept {
    std::swap(elem, node.elem);
    std::swap(left, node.left);
    std::swap(right, node.right);
}

/* ************************************************************************** */

// Copy assignment - NodeLnk
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk &node) {
    elem(node->elem);
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk &&node) noexcept {
    std::swap(elem, node->elem);
    return *this;
}

/* ************************************************************************** */

// Specific member functions - NodeLnk
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild(){
    if(HasRightChild()) {
        return *right;
    }
    else {
        throw std::out_of_range("Right child not found");
    }
}

template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if(HasRightChild()) {
        return *right;
    }
    else {
        throw std::out_of_range("Right child not found");
    }
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
    if(HasLeftChild()) {
        return *left;
    }
    else {
        throw std::out_of_range("Left child not found");
    }
}

/* ************************************************************************** */

template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if(HasLeftChild()) {
        return *left;
    }
    else {
        throw std::out_of_range("Left child not found");
    }
}

/* ************************************************************************** */

// Specific constructor - BinaryTreeLnk from TraversableContainer
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> &tc) {
    size = tc.Size();
    QueueLst<NodeLnk**> queue;
    queue.Enqueue(&root);
    tc.Traverse(
        [&queue](const Data& data){
            NodeLnk *& curr = *queue.HeadNDequeue();
            curr = new NodeLnk(data);
            queue.Enqueue(&curr->left);
            queue.Enqueue(&curr->right);
        }
    );
}

/* ************************************************************************** */

// Specific constructor - BinaryTreeLnk from MappableContainer
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> &&map) noexcept {
    size = map.Size();
    QueueLst<NodeLnk**> queue;
    queue.Enqueue(&root);
    map.Map(
        [&queue](Data& data){
            NodeLnk *& curr = *queue.HeadNDequeue();
            curr = new NodeLnk(std::move(data));
            queue.Enqueue(&curr->left);
            queue.Enqueue(&curr->right);
        }
    );
}

/* ************************************************************************** */

// Copy constructor - BinaryTreeLnk
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk &btl){
    if(btl.root!=nullptr) {
        root = new NodeLnk(*btl.root);
        size = btl.Size();
    }   
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& btl) noexcept {
    std::swap(root, btl.root);
    std::swap(size, btl.size);
}

/* ************************************************************************** */

// Copy assignment - BinaryTreeLnk
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& btl) {
    Clear();
    if (btl.root!=nullptr){
        root = new NodeLnk(*btl.root);
        size = btl.Size();
    }
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& btl) noexcept {
    std::swap(root, btl.root);
    std::swap(size, btl.size);
    return *this;
}

/* ************************************************************************** */

// Specific member functions - BinaryTreeLnk from BinaryTree
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if(!(this->Empty()))
      return *root;
    else
      throw std::length_error("Empty tree");
  };

/* ************************************************************************** */

// Specific member functions - BinaryTreeLnk from MutableBinaryTree
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() {
    if(!(this->Empty()))
      return *root;
    else
      throw std::length_error("Empty tree");
  };

/* ************************************************************************** */

// Specific member function - BinaryTreeLnk from ClearableContainer
template <typename Data>
void BinaryTreeLnk<Data>::Clear() noexcept {
    if (root != nullptr){
        delete root;
        root=nullptr;
    }
    size=0;
}

/* ************************************************************************** */

}
