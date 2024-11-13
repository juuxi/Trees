#include <cstddef>

template <typename T>
struct RB_Tree_node
{
    T key;
    char color;
    RB_Tree_node* parent;
    RB_Tree_node* left_child;
    RB_Tree_node* right_child;
    RB_Tree_node(T _key) : key(_key), parent(nullptr), left_child(nullptr), right_child(nullptr), color('R') {}
    RB_Tree_node(T _key, RB_Tree_node* _parent) : key(_key), parent(_parent), 
    left_child(nullptr), right_child(nullptr), color('R') {}
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
    void small_left_turn(RB_Tree_node<T>*);
    void small_right_turn(RB_Tree_node<T>*);
    void big_left_turn(RB_Tree_node<T>*);
    void big_right_turn(RB_Tree_node<T>*);
    void red_red_violation(RB_Tree_node<T>*);
};

template <typename T>
RB_Tree<T>::RB_Tree(T _key)
{
    root = new RB_Tree_node<T>(_key);
    root->color = 'B';
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
    if (curr == nullptr)
        curr = root;
    if (root == nullptr)
    {
        root = new RB_Tree_node<T>(_key);
        root->color = 'B';
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

    if (new_node->key == _key)
    {
        new_node->color = 'R';
        if (new_node->parent->color != 'B')
            red_red_violation(new_node);
    }
    return new_node;
}

template <typename T>
void RB_Tree<T>::red_red_violation(RB_Tree_node<T>* curr)
{
    RB_Tree_node<T>* grandparent = curr->parent->parent;
    if (curr->parent->key < grandparent->key)
    {
        if (!grandparent->right_child || grandparent->right_child->color == 'B')
        {
            if (curr->key < curr->parent->key)
            {
                curr->parent->color = 'B';
                grandparent->color = 'R';
                small_right_turn(curr->parent);
                if (root->color == 'R')
                    root->color = 'B';
                return;
            }
            curr->color = 'B';
            grandparent->color = 'R';
            big_right_turn(curr);
            if (root->color == 'R')
                root->color = 'B';
            return;
        }
        else
        {
            grandparent->right_child->color = 'B';
            grandparent->color = 'R';
            curr->parent->color = 'B';
            if (grandparent->parent)
            {
                if (grandparent->parent->color == 'R')
                    red_red_violation(grandparent);
            }   
            if (root->color == 'R')
                root->color = 'B';
            return;            
        }
        
    }
    else 
    {
        if (!grandparent->left_child || grandparent->left_child->color == 'B')
        {
            if (curr->key > curr->parent->key)
            {
                curr->parent->color = 'B';
                grandparent->color = 'R';
                small_left_turn(curr->parent);
                if (root->color == 'R')
                    root->color = 'B';
                return;
            }
            big_left_turn(curr);
            curr->color = 'B';
            grandparent->color = 'R';
            if (root->color == 'R')
                root->color = 'B';
            return;
        }
        else
        {
            grandparent->left_child->color = 'B';
            grandparent->color = 'R';
            curr->parent->color = 'B';
            if (grandparent->parent)
            {
                if (grandparent->parent->color == 'R')
                    red_red_violation(grandparent);
            }   
            if (root->color == 'R')
                root->color = 'B';
            return;            
        }
        
    }
}

template <typename T>
void RB_Tree<T>::small_left_turn(RB_Tree_node<T>* curr)
{
    RB_Tree_node<T>* parent = curr->parent; 
    RB_Tree_node<T>* grandparent = parent->parent;
    curr->parent = grandparent;
    parent->right_child = curr->left_child;
    if (curr->left_child)
        curr->left_child->parent = parent;
    curr->left_child = parent;
    if (!grandparent)
        root = curr;
    else 
    {
        if (parent->key < grandparent->key)
            grandparent->left_child = curr;
        else 
            grandparent->right_child = curr;
    }
    parent->parent = curr;
}

template <typename T>
void RB_Tree<T>::small_right_turn(RB_Tree_node<T>* curr)
{
    RB_Tree_node<T>* parent = curr->parent; 
    RB_Tree_node<T>* grandparent = parent->parent;
    curr->parent = grandparent;
    parent->left_child = curr->right_child;
    if (curr->right_child)
        curr->right_child->parent = parent;
    curr->right_child = parent;
    if (!grandparent)
        root = curr;
    else 
    {
        if (parent->key < grandparent->key)
            grandparent->left_child = curr;
        else 
            grandparent->right_child = curr;
    }
    parent->parent = curr;
}

template <typename T>
void RB_Tree<T>::big_left_turn(RB_Tree_node<T>* curr)
{
    small_right_turn(curr);
    small_left_turn(curr);
}

template <typename T>
void RB_Tree<T>::big_right_turn(RB_Tree_node<T>* curr)
{
    small_left_turn(curr);
    small_right_turn(curr);
}