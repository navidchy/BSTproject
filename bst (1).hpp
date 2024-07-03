#ifndef BST_ASSIGNMENT_HPP
#define BST_ASSIGNMENT_HPP

#include <iostream>
#include <algorithm>

template <typename T>
class BST
{
public:
    // We have a Node class with more features now
    // In addition to pointers to the left and right child,
    // there is also a pointer to the parent of Node.  
    // The parent of the root should always be nullptr
    // We also hava a height field to store the height of 
    // a node in the tree.
    class Node 
    {
    public:
        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        // default constructor
        Node(){}
        // constructor that takes one or optionally 2 arguments
        // if only one argument is passed in the second argument 
        // defaults to nullptr
        Node(T k, Node* input_node = nullptr)
        {
            key = k;
            parent = input_node;
        }
    };

private:
    // The BST has two private variables, a pointer to the root
    // and an unsigned integer to hold its size
    // We make the style choice of indicating these are private 
    // data variables by having a trailing underscore in their names.
    Node* root_ = nullptr;
    unsigned int size_ = 0;


public:
    // Default constructor.  No action required on this one.
    BST(); 

    // Destructor.  We implement this for you.
    ~BST();

    //*** Methods for you to implement
    // insert
    // insert the key k into the BST while maintaining the BST property
    // Like std::set, if k is already in the tree then no action is taken
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void insert(T k);

    // successor
    // Return a pointer to the node containing the smallest key larger 
    // than k
    // Return nullptr if k is the largest key in the tree
    // Also return nullptr if k is not in the tree
    //*** For you to implement
    Node* successor(T k);

    // delete the minimum
    // Erase the minimum key in the tree
    // Take no action if tree is empty
    //*** For you to implement
    void delete_min();

    // erase
    // Locate the key k in the tree and remove it
    // If k is not in the tree you do not have to do anything
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void erase(T k);

    // Implement a right rotation about the node pointed to by 
    // node, as described in Lecture 8.6.  This will only be 
    // called when node has a left child.  
    // If left_child points to the left child of *node, 
    // then *left_child becomes the parent of *node, and the 
    // right subtree of *left_child becomes the left subtree of *node.  
    // Node heights should be properly updated after this operation.
    //*** For you to implement
    void rotate_right(Node* node);

    //*** End of methods for you to implement

    // Returns the number of keys in the tree
    // we implement this for you, but it is up to you to correctly
    // update the size_ variable
    unsigned size();

    // Prints out the keys in the tree via an in-order traversal
    // we implement this for you
    void print();

    // Returns a pointer to the node containing the key k
    // We implement this for you
    Node* find(T k);

    // Creates a vector holding the keys in the tree by
    // doing an in-order traversal
    // We implement this for you, it is used in our testing.
    std::vector<T> make_vec();

    // The next two functions are to check your height values 
    // Please do not modify
    std::vector<int> your_postorder_heights();

    std::vector<int> real_postorder_heights();

    // get_root_value returns the value stored at the root
    // It used for testing purposes
    // No action needed on your part
    T get_root_value();

    // Return a pointer to the node containing the minimum key in the tree
    // We implement this for you
    Node* min();

private: 
    // We found it useful to have a "fix_height" function.
    // This assumes that the subtrees rooted at node's children have 
    // correct heights and then walks up the tree from node to the root 
    // correcting the heights.
    // You can imlement this, or correct the heights another way
    void fix_height(Node* node);

    // The rest of these functions are already implemented

    // helper function for the destructor
    void delete_subtree(Node* node);

    // returns pointer to minimum node in subtree rooted by node
    // Assumes node is not nullptr
    Node* min(Node* node);

    // helper function for print
    void print(Node* node);

    // helper function for make_vec
    void make_vec(Node* node, std::vector<T>& vec);

    void your_postorder_heights(Node* node, std::vector<int>& vec);

    int real_postorder_heights(Node* node, std::vector<int>& vec);

};

// Default constructor
// You do not need to change this
template <typename T>
BST<T>::BST()
{
}

// Destructor
// We implement this for you
template <typename T>
BST<T>::~BST()
{
    delete_subtree(root_);
}

// helper function for destructor
template <typename T>
void BST<T>::delete_subtree(Node* node)
{
    if(node==nullptr)
    {
        return;
    }
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

template<typename T>
void BST<T>::fix_height(Node* node)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        node->height = 0;
        
    }

    else {
        int left_child_height = 0, right_child_height = 0;
        if (node->left)
            left_child_height = node->left->height;
        if (node->right)
            right_child_height = node->right->height;

        node->height = std::max(left_child_height, right_child_height) + 1;
    }
    if (node->parent != nullptr)
    {
        fix_height(node->parent);
    }
}

//*** For you to implement
template <typename T>
void BST<T>::insert(T k)
{
    // node will iterate down through the tree starting from the root
    Node* node = root_;
    // prev_node will hold node's parent
    Node* prev_node = node;
    bool went_right;

    if(node == nullptr)
    {
        root_ = new Node(k);
        ++size_;
        return;
    }
    while(node != nullptr)
    {
        prev_node = node;
        if(k < node->key)
        {
            node = node->left;
            went_right = false;
        }
        else if (k > node->key)
        {
            node = node->right;
            went_right = true;
        }
        // item already in set
        else
        {
            return;
        }
    }
    // new node is either left or right child of prev_node
    if(went_right)
    {
        prev_node->right= new Node(k, prev_node);
        prev_node->right->parent = prev_node;
    }
    else
    {
        prev_node->left= new Node(k, prev_node);
        prev_node->left->parent = prev_node;
    }
    fix_height(prev_node);
    ++size_;
    
}

//*** For you to implement
template <typename T>
typename BST<T>::Node* BST<T>::successor(T k)
{
    // There are two cases here.  
    // If the node containing k has a right child, then 
    // the successor will be the minimum node in its right subtree
    // Otherwise, the successor will be the first node with a key 
    // bigger than k on the path from the node with key k to the root.
    // In other words, it is the node where we last took a left turn when 
    // searching for the key k.

Node* key_node = find(k);
    if (key_node != nullptr) {
        if (key_node->right == nullptr) {
            Node* key_node_parent = key_node->parent;
            while (key_node_parent != nullptr) {
                if (key_node_parent->left == key_node)
                    return key_node_parent;
                key_node = key_node_parent;
                key_node_parent = key_node->parent;
            }
        }
        else {
            Node* key_node_successor = key_node->right;
            while (key_node_successor->left != nullptr)
                key_node_successor = key_node_successor->left;
            return key_node_successor;
        }
    }
    return nullptr;
}

//*** For you to implement
template <typename T>
void BST<T>::delete_min()
{

    // if tree is empty just return.
    Node* min_node = min();
    // Now update pointers to remove min_node from the tree

    //delete min_node;
    //--size_;
    //fix_height(start_fix);
     // if tree is empty just return.
    if (min_node != nullptr) {

        Node* successor_to_min = min_node->right;
        
        if (min_node == root_) {
            root_ = successor_to_min;
            if (root_ != nullptr)
                root_->parent = nullptr;
        }

        else {
            min_node->parent->left = successor_to_min;
            if (successor_to_min)
                successor_to_min->parent = min_node->parent;
            fix_height(min_node->parent);
        }
        delete min_node;
        --size_;
    }
}

//*** For you to implement
template <typename T>
void BST<T>::erase(T k)
{
    // Step 1: locate node holding key k
    // simply return if k is not in tree
    // let node_to_remove be a pointer to the node to be removed

    // Step 2: find a node, replacement, to replace node_to_remove
    // We break this down into 3 cases
    // Case 1: node_to_remove has no right child 
    // Case 2: node_to_remove has no left child 
    // Case 3: node_to_remove has both children
    // in this case replacement is successor of node_to_remove
    // There is a further instance of Case 3 that needs special handling.
    // This is where replacement is the right child of node_to_remove.
   
    // Once pointers have been correctly adjusted then don't forget to:
    // delete node_to_remove;
    // --size_;
    // fix the heights from the bottom-most node affected by the changes
    //fix_height(start_fix);
     Node* node_to_remove = find(k);
    if (node_to_remove) {
        Node* replacement = nullptr;
        if (node_to_remove->left && node_to_remove->right) {
            Node* successor_node = successor(k);
            node_to_remove->key = successor_node->key;

            node_to_remove = successor_node;
        }

        if (node_to_remove->left && !node_to_remove->right) {
            replacement = node_to_remove->left;
        }
        else if (node_to_remove->right && !node_to_remove->left) {
            replacement = node_to_remove->right;
        }

        bool wasRoot = false;
        if (node_to_remove == root_) {
            wasRoot = true;
            root_ = replacement;
            if (root_)
                root_->parent = nullptr;
        }
        else {
            if (node_to_remove == node_to_remove->parent->right) {
                node_to_remove->parent->right = replacement;
            }
            else
                node_to_remove->parent->left = replacement;
            if (replacement)
                replacement->parent = node_to_remove; 
        }

        Node* node_to_remove_parent = node_to_remove->parent;
        delete node_to_remove;
        --size_;
        if (!wasRoot) {
            fix_height(node_to_remove_parent);
        }

    }


}

//*** For you to implement
template <typename T>
void BST<T>::rotate_right(Node* node)
{
    // Assumptions: node is not nullptr and must have a left child

    // Node* move_up_node = node->left;  
    
    // There are 3 pairs (parent and child) of pointers to change
    // 1) node's left child becomes move_up_node's right child
    // 2) node's original parent becomes move_up_node's parent
    // 3) move_up_node's right child becomes node

    // Correct height of ancestors of node 
    // fix_height(node);
    Node* move_up_node = node->left;  

     if (move_up_node->right) {
         node->left = move_up_node->right;
         move_up_node->right->parent = node;
     }
     else
         node->left = nullptr;   
     if (node->parent) {
         if (node == node->parent->left)
             node->parent->left = move_up_node;
         else
             node->parent->right = move_up_node;
         move_up_node->parent = node->parent;
     }
     else {
         
         root_ = move_up_node;
         move_up_node->parent = nullptr;
     }
     move_up_node->right = node;
     node->parent = move_up_node;
     fix_height(node);

}

// The rest of the functions below are already implemented

// returns a pointer to the minimum node
template <typename T>
typename BST<T>::Node* BST<T>::min()
{
    if(root_ == nullptr)
    {
        return root_;
    }
    else
    {
        return min(root_);
    }
}

// returns pointer to minimum node in the subtree rooted by node
// Assumes node is not nullptr
template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    } 
    return node;
}

// returns a pointer to node with key k
template <typename T>
typename BST<T>::Node* BST<T>::find(T k)
{
    Node* node = root_;  
    while(node != nullptr && node->key != k)
    {
        node = k < node->key ?  node->left : node->right;
    }
    return node;  
}

template <typename T>
unsigned BST<T>::size()
{
    return size_;
}

// prints out the keys in the tree using in-order traversal
template <typename T>
void BST<T>::print()
{
    print(root_);
}

// you can modify what is printed out to suit your needs
template <typename T>
void BST<T>::print(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    print(node->left);
    std::cout << node->key << " height " << node->height << '\n';
    print(node->right);
}

// This is used in our testing, please do not modify
template <typename T>
typename std::vector<T> BST<T>::make_vec()
{
    std::vector<T> vec;
    vec.reserve(size_);
    make_vec(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::make_vec(Node* node, std::vector<T>& vec)
{
    if(node == nullptr)
    {
        return;
    }
    make_vec(node->left, vec);
    vec.push_back(node->key);
    make_vec(node->right, vec);
    
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::your_postorder_heights(Node* node, std::vector<int>& vec)
{
    if(node == nullptr)
    {
        return;
    }
    your_postorder_heights(node->left, vec);
    your_postorder_heights(node->right, vec);
    vec.push_back(node->height);
}

// This is used for our testing, please do not modify
template <typename T>
int BST<T>::real_postorder_heights(Node* node, std::vector<int>& vec)
{
    if(node == nullptr)
    {
        return -1;
    }
    int left_height = real_postorder_heights(node->left, vec);
    int right_height = real_postorder_heights(node->right, vec);
    int node_height = 1 + std::max(left_height, right_height);
    vec.push_back(node_height);
    return node_height;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::your_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    your_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::real_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    real_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
T BST<T>::get_root_value()
{
    if(root_ == nullptr)
    {
        //std::cout << "Calling get_root_value on empty tree\n";
        T dummy {};
        return dummy;
    }
    else
    {
        return root_->key;
    }
}

#endif

