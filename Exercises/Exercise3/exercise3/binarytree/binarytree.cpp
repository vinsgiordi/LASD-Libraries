
namespace lasd {

/* ************************************************************************** */

// Comparison operators - BinaryTree
template <typename Data>
inline bool BinaryTree<Data>::operator==(const BinaryTree& tree) const noexcept {
    if(this->size != tree.size) { return false; }

    BTPreOrderIterator iter1(*this);
    BTPreOrderIterator iter2(tree);

    while(!(iter1.Terminated() || iter2.Terminated())) {
        if(*iter1 != *iter2) {
            return false;
        }
        ++iter1;
        ++iter2;
    }
    return true;
}

/* ************************************************************************** */

// Specific member function - BinaryTree from TraversableContainer
template <typename Data>
void BinaryTree<Data>::Traverse(const TraverseFun fun) const {
    if(!this->Empty()) {
        PreOrderTraverse(fun);
    }
}

/* ************************************************************************** */

// Specific member function - BinaryTree from PreOrderTraverse
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(const TraverseFun fun) const {
    if(!(this->Empty())) {
        PreOrderTraversable(&this->Root(), fun);
    }
}

/* ************************************************************************** */

// Specific member function - BinaryTree from PostOrderTraverse
template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(const TraverseFun fun) const {
    if(!(this->Empty())) {
        PostOrderTraversable(&this->Root(), fun);
    }
}

/* ************************************************************************** */

// Specific member function - BinaryTree from InOrderTraverse
template <typename Data>
void BinaryTree<Data>::InOrderTraverse(const TraverseFun fun) const {
    if(!(this->Empty())) {
        InOrderTraversable(&this->Root(), fun);
    }
}

/* ************************************************************************** */

// Specific member function - BinaryTree from BreadthTraverse
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(const TraverseFun fun) const {
    if(!(this->Empty())){
        BreadthTraversable(&this->Root(), fun);
    }
}

/* ************************************************************************** */

// Auxiliary functions
template <typename Data>
void BinaryTree<Data>::PreOrderTraversable(const Node* node, const TraverseFun fun) const {
    fun(node->Element());

    if(node->HasLeftChild()) { 
        PreOrderTraversable(&node->LeftChild(), fun); 
    } 
    if(node->HasRightChild()) {
        PreOrderTraversable(&node->RightChild(), fun);
    }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraversable(const Node* node, const TraverseFun fun) const { 
    if(node->HasLeftChild()) {
        PostOrderTraversable(&node->LeftChild(), fun);
    } 
    if(node->HasRightChild()) {
        PostOrderTraversable(&node->RightChild(), fun);
    }

    fun(node->Element());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraversable(const Node* node, TraverseFun fun) const {
    if(node->HasLeftChild()) {
        InOrderTraversable(&node->LeftChild(), fun);
    } 

    fun(node->Element());

    if(node->HasRightChild()) {
        InOrderTraversable (&node->RightChild(), fun);
    }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraversable(const Node* node, TraverseFun fun) const {
    lasd::QueueVec<const BinaryTree<Data>::Node*> queue;
    queue.Enqueue(node);

    while(!queue.Empty()) {
        fun(queue.Head()->Element());

        if(queue.Head()->HasLeftChild()) {
            queue.Enqueue(&(queue.Head()->LeftChild()));
        }
        if(queue.Head()->HasRightChild()) {
            queue.Enqueue(&(queue.Head()->RightChild()));
        }
        queue.Dequeue();
    }
}

/* ************************************************************************** */

// Specific member functions - MutableBinaryTree from PreOrderMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun map) {
    if(!(this->Empty())) {
        PreOrderMappable(&this->Root(), map);
    }
}

/* ************************************************************************** */

// Specific member functions - MutableBinaryTree from PostOrderMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun map) {
    if(!(this->Empty())){
        PostOrderMappable(&this->Root(), map);
    }
}

/* ************************************************************************** */

// Specific member functions - MutableBinaryTree from InOrderMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun map) {
    if(!(this->Empty())){
       InOrderMappable(&this->Root(), map);
    }
}

/* ************************************************************************** */

// Specific member functions - MutableBinaryTree from BreadthMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun map) {
    if(!(this->Empty())){
        BreadthMappable(&this->Root(), map);
    }
}

/* ************************************************************************** */

// Auxiliary functions
template <typename Data>
void MutableBinaryTree<Data>::PreOrderMappable(MutableNode* node, MapFun map) {

    map(node->Element());

    if(node->HasLeftChild()) {
        PreOrderMappable(&node->LeftChild(), map);
    }
    if(node->HasRightChild()) {
        PreOrderMappable(&node->RightChild(), map);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMappable(MutableNode* node, MapFun map) {

    if(node->HasLeftChild()) {
        PostOrderMappable(&node->LeftChild(), map);
    }
    if(node->HasRightChild()) {
        PostOrderMappable(&node->RightChild(), map);
    }

    map(node->Element());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMappable(MutableNode* node, MapFun map) {

    if(node->HasLeftChild()) {
        InOrderMappable(&node->LeftChild(), map);
    }
    
    map(node->Element());

    if(node->HasRightChild()) {
        InOrderMappable(&node->RightChild(), map);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMappable(MutableNode* node, MapFun map)  {
    
    lasd::QueueVec<MutableBinaryTree<Data>::MutableNode*> queue;
    queue.Enqueue(node);

    while(!queue.Empty()) {
        map(queue.Head()->Element());

        if(queue.Head()->HasLeftChild()) {
            queue.Enqueue(&(queue.Head()->LeftChild()));
        }
        if(queue.Head()->HasRightChild()) {
            queue.Enqueue(&(queue.Head()->RightChild()));
        }
        queue.Dequeue();
    }
}

/* ************************************************************************** */

// Specific constructor - BTPreOrderIterator
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree) {
    if(!tree.Empty()) {
        root = curr = &tree.Root();
    }
}

/* ************************************************************************** */

// Copy constructor - BTPreOrderIterator
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& tree) : stk(tree.stk) {
    root = tree.root;
    curr = tree.curr;
}

// Move constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& tree) noexcept : stk(std::move(tree.stk)) {
    std::swap(root, tree.root);
    std::swap(curr, tree.curr);
}

/* ************************************************************************** */

// Copy assignment - BTPreOrderIterator
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& tree) {
    curr = tree.curr;
    root = tree.root;
    stk = tree.stk;
    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& tree) noexcept {
    std::swap(root, tree.root);
    std::swap(curr, tree.curr);
    std::swap(stk, tree.stk);
    return *this;
}

/* ************************************************************************** */

// Comparison operators - BTPreOrderIterator
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& tree) const noexcept {
    return (curr == tree.curr && stk == tree.stk);
}

/* ************************************************************************** */

// Specific member function - BTPreOrderIterator from Iterator
template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator terminated");
    } else {
        return curr->Element();
    }
}

/* ************************************************************************** */

// Specific member functions - BTPreOrderIterator from ForwardIterator
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if(!Terminated()){
        if(curr->HasLeftChild()){
            if(curr->HasRightChild())
                stk.Push(&curr->RightChild());
            curr=&(curr->LeftChild());
        }
        else if(curr->HasRightChild())
            curr=&(curr->RightChild());
        else if (!stk.Empty())
            curr=stk.TopNPop();
        else
            curr=nullptr;
    }
    else
        throw std::out_of_range("Iterator terminated");
    return *this;
}

/* ************************************************************************** */

// Copy assignment - BTPreOrderMutableIterator
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& tree) {
    this->curr = tree.curr;
    this->root = tree.root;
    this->stk = tree.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& tree) noexcept {
    std::swap(this->curr, tree.curr);
    std::swap(this->root, tree.root);
    std::swap(this->stk, tree.stk);

    return *this;
}

/* ************************************************************************** */

// Specific member functions from MutableIterator
template <typename Data>
Data& BTPreOrderMutableIterator<Data>::operator*() {
    if(this->curr!=nullptr)  {
        return const_cast<Data&>((this->curr)->Element());
    }
    else {
        throw std::out_of_range("Error: out of range"); 
    }
};

/* ************************************************************************** */

// Specific constructor - BTPostOrderIterator
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree) {
    if(tree.Empty()) {
        root = nullptr;
    }
    else {
        root = &tree.Root();
    }
    curr = LeftLeaf(root);
}

/* ************************************************************************** */

// Copy constructor - BTPostOrderIterator
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& tree) {
    stk = tree.stk;
    root = tree.root;
    curr = tree.curr;
}

// Move constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& tree) noexcept : stk(std::move(tree.stk)) {
    std::swap(curr, tree.curr);
    std::swap(root, tree.root);
}

/* ************************************************************************** */

// Specific functions
template <typename Data>
const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::LeftLeaf(const typename BinaryTree<Data>::Node* exists) {
    if(exists != nullptr) {
        while(exists->HasLeftChild()) {
            stk.Push(exists);
            exists = &(exists->LeftChild());
        }
        if(exists->HasRightChild()) {
            stk.Push(exists);
            exists = &(exists->RightChild());
            exists = LeftLeaf(exists);
        }
    }
    
    return exists;
}

/* ************************************************************************** */

// Copy assignment - BTPostOrderIterator
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& tree) {
    curr = tree.curr;
    root = tree.root;
    stk = tree.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& tree) noexcept {
    std::swap(curr, tree.curr);
    std::swap(root, tree.root);
    std::swap(stk, tree.stk);

    return *this;
}

/* ************************************************************************** */

// Comparison operators - BTPostOrderIterator
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& tree) const noexcept {
    return (curr == tree.curr && stk == tree.stk);
}

/* ************************************************************************** */

// Specific member functions - BTPOrderIterator from Iterator
template <typename Data>
const Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator terminated");
    } else {
        return curr->Element();
    }
}

/* ************************************************************************** */

// Specific member functions - BTPostOrderIterator from ForwardIterator
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if(Terminated()) {
        throw std::out_of_range("Iterator terminated");
    }

    if(stk.Empty()) { 
        curr = nullptr;
    } else {
        if(stk.Top()->HasRightChild() && ! (&stk.Top()->RightChild() == curr)) {
            curr = &stk.Top()->RightChild();
            curr = LeftLeaf(curr);
        } else {
            curr = stk.TopNPop();
        }
    }

    return *this;
}

/* ************************************************************************** */

// Copy assignment - BTPostOrderMutableIterator
template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& tree) {
    this->curr = tree.curr;
    this->root = tree.root;
    this->stk = tree.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& tree) noexcept {
    std::swap(this->curr, tree.curr);
    std::swap(this->root, tree.root);
    std::swap(this->stk, tree.stk);

    return *this;

}

/* ************************************************************************** */

// Specific member functions - BTPostOrderIterator from MutableIterator
template <typename Data>
Data& BTPostOrderMutableIterator<Data>::operator*() {
    if(this->curr!=nullptr) {
        return const_cast<Data&>((this->curr)->Element());
    }
    else {
        throw std::out_of_range("BTPostOrderMutableIterator is out of range in operator*()");
    }
};

/* ************************************************************************** */

// Specific functions - BTInOrderIterator
template <typename Data>
const typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::FindLeftLeaf(const typename BinaryTree<Data>::Node* exists) {
    while(exists != nullptr && (exists->HasLeftChild())) {
        stk.Push(exists);
        exists = &exists->LeftChild();
    }

    return exists;
}

/* ************************************************************************** */

// Specific constructor - BTInOrderIterator
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
    if(bt.Empty() != 0) {
        root = nullptr;
    }
    else {
        root = &bt.Root();
    }
    curr = FindLeftLeaf(root);
}

/* ************************************************************************** */

// Copy constructor - BTInOrderIterator
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& tree) {
    stk = tree.stk;
    root = tree.root;
    curr = tree.curr;
}

// Move Iterator
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& tree) noexcept : stk(std::move(tree.stk)) {
    std::swap(curr, tree.curr);
    std::swap(root, tree.root); 
}

/* ************************************************************************** */

// Copy assignment - BTInOrderIterator
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& tree) {
    curr = tree.curr ;
    root = tree.root;
    stk = tree.stk;

    return *this;
}

// Move assignment 
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& tree) noexcept {
    std::swap(curr, tree.curr);
    std::swap(root, tree.root);
    std::swap(stk, tree.stk);

    return *this;
}

/* ************************************************************************** */

// Comparison operators - BTInOrderIterator
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &tree) const noexcept {
    return (curr == tree.curr && stk == tree.stk);
}

/* ************************************************************************** */

// Specific member functions - BTInOrderIterator from Iterator
template <typename Data>
const Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator terminated");
    } else {
        return curr->Element();
    }
}

/* ************************************************************************** */

// Specific member functions BTInOrderIterator from ForwardIterator
template <typename Data>
BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator++() {
    if(!(Terminated())){
        if((stk.Empty()) && !(curr->HasRightChild())) {
            curr=nullptr;
        }
        else { 
            if(curr->HasRightChild()){
                curr = FindLeftLeaf(&curr->RightChild());
            }
            else {
                curr = stk.TopNPop();
            }
        }
    }
    else {
        throw std::out_of_range("Iterator terminated");
    }

    return *this;
}

/* ************************************************************************** */

// Copy assignment - BTInOrderMutableIterator
template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator& tree) {
    this->curr = tree.curr;
    this->root = tree.root;
    this->stk = tree.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator&& tree) noexcept {
    std::swap(this->curr, tree.curr);
    std::swap(this->root, tree.root);
    std::swap(this->stk, tree.stk);

    return *this;
}

/* ************************************************************************** */

// Specific member functions BTInOrderMutableIterator from MutableIterator
template <typename Data>
Data& BTInOrderMutableIterator<Data>::operator*() {
    if(this->curr!=nullptr) {
        return const_cast<Data&>((this->curr)->Element());
    }
    else {
        throw std::out_of_range("Error: out of range"); 
    }
};

/* ************************************************************************** */

// Specific constructor - BTBreadthIterator 
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
    if(bt.Empty()) {
        root = curr = nullptr;
    }
    else {
        root = curr = &bt.Root();
    }
}

/* ************************************************************************** */

// Copy constructor - BTBreadthIterator
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator& tree) {
    queue = tree.queue;
    root = curr = tree.curr;
}

// Move constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& tree) noexcept : queue(std::move(tree.queue)) {
    std::swap(root, tree.root);
    std::swap(curr, tree.curr); 
}

/* ************************************************************************** */

// Copy assigment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& tree) {
    curr = tree.curr;
    root = tree.root;
    queue = tree.queue;

    return *this;
}

// Move assigmment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& tree) noexcept {
    std::swap(curr, tree.curr);
    std::swap(root, tree.root);
    std::swap(queue, tree.queue);
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &tree) const noexcept {
    return (curr == tree.curr && queue == tree.queue);
}

/* ************************************************************************** */

// Specific member functions - BTBreadthIterator from MutableIterator
template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Error: out of range");
    }
    else {
        return curr->Element();
    }
}

/* ************************************************************************** */

// Specific member functions - BTBreadthIterator from ForwardIterator

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if (!(Terminated())) {
        if (curr->HasLeftChild()){
            queue.Enqueue(&(curr->LeftChild())); 
        }
        if (curr->HasRightChild()){
            queue.Enqueue(&(curr->RightChild()));
        }
        if (!queue.Empty()){
            curr = queue.HeadNDequeue();
        }
        else{
            curr = nullptr;
        }
    }
    else{
        throw std::out_of_range("Error: out of range");
    }

    return *this;
}

/* ************************************************************************** */

// Copy assignment - BTBreadthMutableIterator 
template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& tree) {
    this->curr = tree.curr;
    this->root = tree.root;
    this->queue = tree.queue;

    return *this;
}

// Move assigment 
template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& tree) noexcept {
    std::swap(this->curr, tree.curr);
    std::swap(this->root, tree.root);
    std::swap(this->queue, tree.queue);

    return *this;
}

/* ************************************************************************** */

// Specific member functions - BTBreadthMutableIterator from Iterator
template <typename Data>
Data& BTBreadthMutableIterator<Data>::operator*() {
    if(this->curr!=nullptr) {
        return const_cast<Data&>((this->curr)->Element());
    }
    else {
        throw std::out_of_range("Error: out of range");
    } 
};

/* ************************************************************************** */

}
