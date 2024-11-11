#include <cstddef>
#include <iostream>

template <typename T>
struct Binary_Tree_node
{
    T key;
    Binary_Tree_node* parent;
    Binary_Tree_node* left_child;
    Binary_Tree_node* right_child;
    Binary_Tree_node(T _key) : key(_key), parent(nullptr), left_child(nullptr), right_child(nullptr) {}
    Binary_Tree_node(T _key, Binary_Tree_node* _parent) : key(_key), parent(_parent), left_child(nullptr), right_child(nullptr) {}
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
    Binary_Tree_node<T>* add_left_child(Binary_Tree_node<T>*, T);
    Binary_Tree_node<T>* add_right_child(Binary_Tree_node<T>*, T);
};

template <typename T>
Binary_Tree<T>::Binary_Tree(T _key)
{
    root = new Binary_Tree_node<T>(_key);
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
Binary_Tree_node<T>* Binary_Tree<T>::add_left_child(Binary_Tree_node<T>* curr, T _key)
{
    Binary_Tree_node<T>* new_child = new Binary_Tree_node<T>(_key, curr);
    curr->left_child = new_child;
    return new_child;
}

template <typename T>
Binary_Tree_node<T>* Binary_Tree<T>::add_right_child(Binary_Tree_node<T>* curr, T _key)
{
    Binary_Tree_node<T>* new_child = new Binary_Tree_node<T>(_key, curr);
    curr->right_child = new_child;
    return new_child;
}