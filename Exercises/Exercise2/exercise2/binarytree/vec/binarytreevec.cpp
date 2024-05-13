
namespace lasd {

/* ************************************************************************** */

// Specific constructor - NodeVec
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &data, unsigned long int index, BinaryTreeVec<Data>* Tree) {
    this->Tree = Tree;
    Tree->elements[index]=data;  
    this->index=index;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& data, unsigned long int index, BinaryTreeVec<Data>* Tree) noexcept {
    this->Tree = Tree;
    std::swap(Tree->data[index], data);
    this->index=index;
}

/* ************************************************************************** */

// Specific member functions - NodeVec
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (index*2+1<(Tree->NodeArray).Size()) && ((Tree->NodeArray)[index*2+1] != nullptr);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return index*2+2<(Tree->NodeArray).Size() && (Tree->NodeArray)[index*2+2] != nullptr;
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(HasLeftChild()) {
        return *(Tree->NodeArray[index*2+1]);
    }
    else {
        throw std::out_of_range("Left child not found");
    }
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if(HasLeftChild()) {
        return *(Tree->NodeArray[index*2+1]);
    }
    else {
        throw std::out_of_range("Left child not found");
    }
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(HasRightChild()) {
        return *(Tree->NodeArray[index*2+2]);
    }
    else {
        throw std::out_of_range("Right child not found");
    }
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() {
    if(HasRightChild()) {
        return *(Tree->NodeArray[index*2+2]);
    }
    else {
        throw std::out_of_range("Right child not found");
    }
}

/* ************************************************************************** */

// Specific constructor - BinaryTreeVec from TraversableContainer
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& tc) {
    this->Resize(tc.Size());
    NodeArray.Resize(tc.Size());
    int index = 0;
    this->size = tc.Size();
    tc.Traverse(
        [this, &index](const Data& data){
            this->NodeArray[index] = new NodeVec(data, index, this);
            index++;
        }
    );

}

/* ************************************************************************** */

// Specific constructor - BinaryTreeVec from MappableContainer
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& map) noexcept {
    this->Resize(map.Size());
    NodeArray.Resize(map.Size());
    int index = 0;
    map.Map(
        [this, &index](Data& data){
            this->NodeArray[index] = new NodeVec(std::move(data), index, this);
            index++;
        }
    );
}

/* ************************************************************************** */

// Copy constructor - BinaryTreeVec
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
    this->Clear();
    this->Resize(btv.Size());

    NodeArray.Resize(btv.Size());

    for(unsigned long int index=0; index<this->Size(); index++) {
        NodeArray[index] = new NodeVec(btv.elements[index], index, this);
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv) noexcept {
    std::swap(this->size, btv.size);
    std::swap(elements, btv.elements);
    std::swap(NodeArray, btv.NodeArray);

    for(unsigned long int index=0; index<size; index++) {
        NodeArray[index]->Tree = this;
    }
}

/* ************************************************************************** */

// Destructor - BinaryTreeVec
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    for(unsigned long int index=0; index<NodeArray.Size(); index++){
        if(NodeArray[index]!=nullptr) {
            delete NodeArray[index];
        }
    }
}

/* ************************************************************************** */

// Copy assignment - BinaryTreeVec
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& btv) {
    this->Resize(btv.Size());
    NodeArray.Resize(btv.Size());

    for(unsigned long int index=0; index<this->Size(); index++) {
        NodeArray[index] = new NodeVec(btv.elements[index], index, this);
    }

    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec &&btv) noexcept {
    std::swap(elements, btv.elements);
    std::swap(NodeArray, btv.NodeArray);
    std::swap(size, btv.size);

    for(unsigned long int index=0; index<size; index++) {
        NodeArray[index]->Tree = this;
    }
    for(unsigned long int index=0; index<btv.size; index++) {
        btv.NodeArray[index]->Tree = &btv;
    }

    return *this;
}

/* ************************************************************************** */

// Specific member functions - BinaryTreeVec from BinaryTree
template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if(!this->Empty()) {
        return *NodeArray[0];
    }
    else {
        throw std::length_error("Empty tree");
    }
}

/* ************************************************************************** */

// Specific member functions - BinaryTreeVec from MutableBinaryTree
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if(!this->Empty()) {
        return *NodeArray[0];
    }
    else {
        throw std::length_error("Empty tree");
    }
}

/* ************************************************************************** */

// Specific member functions - BinaryTreeVec from ClearableContainer
template <typename Data>
inline void BinaryTreeVec<Data>::Clear(){
    for(unsigned long int index=0; index<this->Size(); index++){
        if(NodeArray[index]!=nullptr){
            delete NodeArray[index];
            NodeArray[index]=nullptr;
        }
    }
    Vector<Data>::Clear();
}

/* ************************************************************************** */

}