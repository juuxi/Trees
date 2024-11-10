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
    void deep_traverse(Binary_Tree_node<T>*);
};

template <typename T>
void Binary_Tree<T>::deep_traverse(Binary_Tree_node<T>* curr) //central
{
    if (curr->left_child)
        deep_traverse(curr->left_child);
    std::cout << curr->key;
    if (curr->right_child)
        deep_traverse(curr->right_child);
}