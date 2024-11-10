#include <cstddef>
#include <iostream>

template <typename T>
struct Binary_Tree_node
{
    T key;
    Binary_Tree_node* parent;
    Binary_Tree_node* left_child;
    Binary_Tree_node* right_child;
};

template <typename T>
class Binary_Tree 
{
    Binary_Tree_node<T>* root;
    size_t height;
public:
    Binary_Tree() : root(nullptr), height(0) {}
    Binary_Tree(T);
    void deep_traverse(Binary_Tree_node<T>*);
    void add_left_child(Binary_Tree_node<T>*, T);
    void add_right_child(Binary_Tree_node<T>*, T);
};

template <typename T>
Binary_Tree<T>::Binary_Tree(T _key)
{
    root = new Binary_Tree_node<T>;
    root->left_child = nullptr;
    root->right_child = nullptr;
    root->parent = nullptr;
    root->key = _key;
}

template <typename T>
void Binary_Tree<T>::deep_traverse(Binary_Tree_node<T>* curr) //central
{
    if (curr->left_child)
        deep_traverse(curr->left_child);
    std::cout << curr->key;
    if (curr->right_child)
        deep_traverse(curr->right_child);
}

template <typename T>
void Binary_Tree<T>::add_left_child(Binary_Tree_node<T>* curr, T _key)
{
    Binary_Tree_node<T>* new_child = new Binary_Tree_node<T>;
    curr->left_child = new_child;
    new_child->parent = curr;
    new_child->key = _key;
}

template <typename T>
void Binary_Tree<T>::add_right_child(Binary_Tree_node<T>* curr, T _key)
{
    Binary_Tree_node<T>* new_child = new Binary_Tree_node<T>;
    curr->right_child = new_child;
    new_child->parent = curr;
    new_child->key = _key;
}