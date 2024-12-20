#include <cstddef>
#include <queue>
#include <iostream>
#include "stack.cpp"

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
    ~RB_Tree();
    RB_Tree_node<T>* add(T);
    RB_Tree_node<T>* search(RB_Tree_node<T>*, T);
    void delete_node(T);
    void breadth_first_search();
    void depth_first_search_forward();
    void depth_first_search_central();
    void depth_first_search_backward();
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
    RB_Tree_node<T>* search_rightmost_in_left(RB_Tree_node<T>*);
};

template <typename T>
RB_Tree<T>::RB_Tree(T _key)
{
    root = new RB_Tree_node<T>(_key);
    root->color = 'B';
}

template <typename T>
RB_Tree<T>::~RB_Tree()
{
    while (root)
        delete_node(root->key);
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
    if (!curr->parent)
    {
        if (curr->right_child)
        {
            RB_Tree_node<T>* sub = search_leftmost_in_right(curr);
            T new_key = sub->key;
            delete_node(sub->key);
            curr->key = new_key;
            return;
        }
        if (curr->left_child)
        {
            RB_Tree_node<T>* sub = search_rightmost_in_left(curr);
            T new_key = sub->key;
            delete_node(sub->key);
            curr->key = new_key;
            return;
        }
        delete curr;
        root = nullptr;
        return;
    }
    if (!curr->left_child && !curr->right_child)
    {
        if (curr->color == 'B')
            black_delete_violation(curr);
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
        //black_delete_violation(curr->left_child);
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
        //black_delete_violation(curr->left_child);
        curr->right_child->parent = parent;
        if (curr->key < parent->key)
            parent->left_child = curr->right_child;
        else 
            parent->right_child = curr->right_child;
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
RB_Tree_node<T>* RB_Tree<T>::search_rightmost_in_left(RB_Tree_node<T>* curr)
{
    curr = curr->left_child;
    while (curr->right_child)
        curr = curr->right_child;
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
    char brother_left_child_color;
    char brother_right_child_color;
    if (!brother_left_child)
        brother_left_child_color = 'B';
    else 
        brother_left_child_color = brother_left_child->color;
    if (!brother_right_child)
        brother_right_child_color = 'B';
    else 
        brother_right_child_color = brother_right_child->color;

    if (parent->color == 'R' && brother->color == 'B' && brother_left_child_color == 'B' && brother_right_child_color == 'B')
    {
        parent->color = 'B';
        brother->color = 'R';
        return;
    }
    
    if (brother->color == 'R')
    {
        if (curr->key < parent->key)
            small_left_turn(brother);
        else
            small_right_turn(brother);
        brother->color = 'B';
        parent->color = 'R';
        black_delete_violation(curr);
        return;
    }

    if (parent->color == 'B' && brother->color == 'B' && brother_left_child_color == 'B' && brother_right_child_color == 'B')
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
        if (brother->color == 'B' && brother_right_child_color == 'B' && brother_left_child_color == 'R')
        {
            small_right_turn(brother_left_child);
            brother_left_child->color = 'B';
            brother->color = 'R';
            black_delete_violation(curr);
            return;
        }
    }
    else 
    {
        if (brother->color == 'B' && brother_left_child_color == 'R')
        {
            small_right_turn(brother);
            brother->color = parent->color;
            parent->color = 'B';
            brother_left_child->color = 'B';
            return;
        }
        if (brother->color == 'B' && brother_left_child_color == 'B' && brother_right_child_color == 'R')
        {
            small_left_turn(brother_right_child);
            brother_right_child->color = 'B';
            brother->color = 'R';
            black_delete_violation(curr);
            return;
        }
    }
}

template <typename T>
void RB_Tree<T>::breadth_first_search()
{
    std::queue<RB_Tree_node<T>*> q;
    q.push(root);
    while(!q.empty())
    {
        RB_Tree_node<T>* curr = q.front();
        q.pop();
        std::cout << curr->key << " ";
        if (curr->left_child)
            q.push(curr->left_child);
        if (curr->right_child)
            q.push(curr->right_child);
    }
}

template <typename T>
void RB_Tree<T>::depth_first_search_forward()
{
    Stack<RB_Tree_node<T>*> s;
    s.push_front(root);
    while (!s.is_empty())
    {
        RB_Tree_node<T>* curr = s.top();
        std::cout << curr->key << " ";
        s.pop_front();
        if (curr->right_child)
            s.push_front(curr->right_child);
        if (curr->left_child)
            s.push_front(curr->left_child);
    }
}

template <typename T>
void RB_Tree<T>::depth_first_search_central()
{
    Vector<RB_Tree_node<T>*> visited(1);
    Stack<RB_Tree_node<T>*> s;
    s.push_front(root);
    while (!s.is_empty())
    {
        RB_Tree_node<T>* curr = s.top();
        if (curr->left_child && !visited.incl(curr->left_child))
        {
            s.push_front(curr->left_child);
        }
        else
        {
            std::cout << curr->key << " ";
            visited.push_back(curr);
            s.pop_front();
            if (curr->right_child && !visited.incl(curr->right_child))
                s.push_front(curr->right_child);
        }
    }
}

template <typename T>
void RB_Tree<T>::depth_first_search_backward()
{
    Vector<RB_Tree_node<T>*> visited(1);
    Stack<RB_Tree_node<T>*> s;
    s.push_front(root);
    while (!s.is_empty())
    {
        RB_Tree_node<T>* curr = s.top();
        if (curr->left_child && !visited.incl(curr->left_child))
        {
            s.push_front(curr->left_child);
        }
        else if (curr->right_child && !visited.incl(curr->right_child))
                s.push_front(curr->right_child);
        else
        {
            std::cout << curr->key << " ";
            visited.push_back(curr);
            s.pop_front();
            
        }
    }
}