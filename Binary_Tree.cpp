#include <cstddef>

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
    Binary_Tree_node* root;
    size_t height;
public:
    Binary_Tree();
    deep_traverse();
};

template <typename T>
Binary_Tree<T>::Binary_Tree()
{
    root = nullptr;
    height = 0;
}