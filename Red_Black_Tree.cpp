#include <cstddef>

template <typename T>
struct RB_Tree_node
{
    T key;
    char color;
    RB_Tree_node* parent;
    RB_Tree_node* left_child;
    RB_Tree_node* right_child;
    RB_Tree_node(T _key) : key(_key), parent(nullptr), left_child(nullptr), right_child(nullptr), color("R") {}
    RB_Tree_node(T _key, RB_Tree_node* _parent) : key(_key), parent(_parent), 
    left_child(nullptr), right_child(nullptr), color("R") {}
};

template <typename T>
class RB_Tree
{
    RB_Tree_node<T>* root;
public: 
    RB_Tree() : root(nullptr) {}
    RB_Tree(T);
    RB_Tree_node<T>* add(RB_Tree_node<T>*, T);
private:
    RB_Tree_node<T>* add_left_child(RB_Tree_node<T>*, T);
    RB_Tree_node<T>* add_right_child(RB_Tree_node<T>*, T);
};

template <typename T>
RB_Tree<T>::RB_Tree(T _key)
{
    root = new RB_Tree_node<T>(_key);
    root->color = "B";
}

template <typename T>
RB_Tree_node<T>* RB_Tree<T>::add_left_child(RB_Tree_node<T>* curr, T _key)
{
    RB_Tree_node<T>* new_child = new RB_Tree_node<T>(_key, curr);
    curr->left_child = new_child;
    return new_child;
}

template <typename T>
RB_Tree_node<T>* RB_Tree<T>::add_right_child(RB_Tree_node<T>* curr, T _key)
{
    RB_Tree_node<T>* new_child = new RB_Tree_node<T>(_key, curr);
    curr->right_child = new_child;
    return new_child;
}

template <typename T>
RB_Tree_node<T>* RB_Tree<T>::add(RB_Tree_node<T>* curr, T _key)
{
    if (root == nullptr)
    {
        root = new RB_Tree_node<T>(_key);
        root->color = "B";
        return root;
    }
    
    RB_Tree_node<T>* new_node;

    if (_key < curr->key)
    {
        if (curr->left_child == nullptr)
            new_node = add_left_child(curr, _key);
        else 
            add(curr->left_child, _key);
    }

    if (_key > curr->key)
    {
        if (curr->right_child == nullptr)
            new_node = add_right_child(curr, _key);
        else 
            add(curr->right_child, _key);
    }

    new_node->color = "R";
    if (new_node->parent->color == "B")
        return new_node;
    else 
    {
        //red-red violation
    }
}