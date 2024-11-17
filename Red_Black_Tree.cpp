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
    RB_Tree_node<T>* add(T);
    RB_Tree_node<T>* search(RB_Tree_node<T>*, T);
    void delete_node(T);
private:
    RB_Tree_node<T>* add_left_child(RB_Tree_node<T>*, T);
    RB_Tree_node<T>* add_right_child(RB_Tree_node<T>*, T);
    void small_left_turn(RB_Tree_node<T>*);
    void small_right_turn(RB_Tree_node<T>*);
    void big_left_turn(RB_Tree_node<T>*);
    void big_right_turn(RB_Tree_node<T>*);
    void red_red_violation(RB_Tree_node<T>*);
    void black_delete_violation(RB_Tree_node<T>*);
    RB_Tree_node<T>* search_leftmost_in_right(RB_Tree_node<T>*);
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
RB_Tree_node<T>* RB_Tree<T>::search(RB_Tree_node<T>* curr, T _key)
{
    if (curr == nullptr)
        curr = root;
    if (root == nullptr)
        return nullptr;
    if (curr->key == _key)
        return curr;
    if (_key < curr->key)
    {
        if (curr->left_child)
            search(curr->left_child, _key);
        else 
            return curr;
    }
    else 
    {
        if (curr->right_child)
            search(curr->right_child, _key);
        else 
            return curr;
    }
}

template <typename T>
RB_Tree_node<T>* RB_Tree<T>::add(T _key)
{
    RB_Tree_node<T>* curr = search(nullptr, _key);
    if (root == nullptr)
    {
        root = new RB_Tree_node<T>(_key);
        root->color = 'B';
        return root;
    }
    
    RB_Tree_node<T>* new_node;
    if (_key == curr->key)
        return curr;
    if (_key < curr->key)
        new_node = add_left_child(curr, _key);
    if (_key > curr->key)
        new_node = add_right_child(curr, _key);
    new_node->color = 'R';
    if (new_node->parent->color != 'B')
        red_red_violation(new_node);
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

template <typename T>
void RB_Tree<T>::delete_node(T _key)
{
    RB_Tree_node<T>* curr = search(nullptr, _key);
    if (curr->key != _key)
        return;
    if (!curr->left_child && !curr->right_child)
    {
        if (curr->key < curr->parent->key)
            curr->parent->left_child = nullptr;
        else
            curr->parent->right_child = nullptr;
        delete curr;
        return;
    }
    if (curr->left_child && !curr->right_child)
    {
        RB_Tree_node<T>* parent = curr->parent;
        if (curr->color == 'R' || curr->left_child->color == 'R')
        {
            curr->left_child->parent = parent;
            if (curr->key < parent->key)
                parent->left_child = curr->left_child;
            else 
                parent->right_child = curr->left_child;
            if (curr->color == 'B')
                curr->left_child->color = 'B';
            delete curr;
            return;
        }
        curr->left_child->parent = parent;
        if (curr->key < parent->key)
            parent->left_child = curr->left_child;
        else 
            parent->right_child = curr->left_child;
        black_delete_violation(curr->left_child);
        delete curr;
        return;
    }

    if (!curr->left_child && curr->right_child)
    {
        RB_Tree_node<T>* parent = curr->parent;
        if (curr->color == 'R' || curr->right_child->color == 'R')
        {
            curr->right_child->parent = parent;
            if (curr->key < parent->key)
                parent->left_child = curr->right_child;
            else 
                parent->right_child = curr->right_child;
            if (curr->color == 'B')
                curr->right_child->color = 'B';
            delete curr;
            return;
        }
        curr->left_child->parent = parent;
        if (curr->key < parent->key)
            parent->left_child = curr->left_child;
        else 
            parent->right_child = curr->left_child;
        black_delete_violation(curr->right_child);
        delete curr;
        return;
    }
    if (curr->left_child && curr->right_child)
    {
        RB_Tree_node<T>* sub = search_leftmost_in_right(curr);
        T new_key = sub->key;
        delete_node(sub->key);
        curr->key = new_key;
    }
}

template <typename T>
RB_Tree_node<T>* RB_Tree<T>::search_leftmost_in_right(RB_Tree_node<T>* curr)
{
    curr = curr->right_child;
    while (curr->left_child)
        curr = curr->left_child;
    return curr;
}

template <typename T>
void RB_Tree<T>::black_delete_violation(RB_Tree_node<T>* curr)
{
    RB_Tree_node<T>* parent = curr->parent;
    RB_Tree_node<T>* brother;
    if (curr->key < parent->key)
        brother = parent->right_child;
    else
        brother = parent->left_child;
    RB_Tree_node<T>* brother_left_child = brother->left_child;
    RB_Tree_node<T>* brother_right_child = brother->right_child;

    if ((parent->color == 'R' && brother->color == 'B' && !brother_left_child && !brother_right_child) || 
    (parent->color == 'R' && brother->color == 'B' && brother_left_child->color == 'B' && brother_right_child->color == 'B'))
    {
        parent->color = 'B';
        brother->color = 'R';
        return;
    }
    
    if (brother->color == 'R')
    {
        small_left_turn(brother);
        brother->color = 'B';
        parent->color = 'R';
        black_delete_violation(parent);
        return;
    }

    if ((parent->color == 'B' && brother->color == 'B' && !brother_left_child && !brother_right_child) || 
    (parent->color == 'B' && brother->color == 'B' && brother_left_child->color == 'B' && brother_right_child->color == 'B'))
    {
        brother->color = 'R';
        if (parent != root)
            black_delete_violation(parent);
        return;
    }

    if (curr->key < parent->key)
    {
        if (brother->color == 'B' && brother_right_child->color == 'R')
        {
            small_left_turn(brother);
            brother->color = parent->color;
            parent->color = 'B';
            brother_right_child->color = 'B';
            return;
        }
        if (brother->color == 'B' && brother_right_child->color == 'B' && brother_left_child->color == 'R')
        {
            small_right_turn(brother_left_child);
            black_delete_violation(curr);
            return;
        }
    }
    else 
    {
        if (brother->color == 'B' && brother_left_child->color == 'R')
        {
            small_right_turn(brother);
            brother->color = parent->color;
            parent->color = 'B';
            brother_left_child->color = 'B';
            return;
        }
        if (brother->color == 'B' && brother_left_child->color == 'B' && brother_right_child->color == 'R')
        {
            small_left_turn(brother_right_child);
            black_delete_violation(curr);
            return;
        }
    }
}