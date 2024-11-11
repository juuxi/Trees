#include <iostream>
#include <fstream>
#include "Binary_Tree.cpp"
#include "stack.cpp"

int main()
{
    std::string input;
    Stack<char> stack;
    std::ifstream f("brace_input.txt");
    if (f)
        getline(f, input);
    if (input[0] != '(')
    {
        std::cout << "Error!" << std::endl;
        return 1;
    }
    stack.push_front('(');
    input.erase(0, 1);
    int root = 0;
    if (input.find('(') > 5)
    {
        std::cout << "Error" << std::endl;
        return 2;
    }
    for (int i = 0; i < input.find('('); i++)
        root = root*10 + input[i]-'0';
    input.erase(0, input.find('('));
    stack.push_front('(');
    input.erase(0, 1);
    Binary_Tree<int> Tree(root);
    Binary_Tree_node<int>* curr_parent = Tree.get_root();
    int curr_node_val = 0;
    bool right_child_flag = false;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
        {
            stack.push_front('(');
            if (input[i-1] != '(' && input[i-1] != ')')
            {
                if (right_child_flag)
                    curr_parent = Tree.add_right_child(curr_parent, curr_node_val);
                else
                    curr_parent = Tree.add_left_child(curr_parent, curr_node_val);
                right_child_flag = false;
                curr_node_val = 0;
            }
            if (input[i-1] == ')')
                right_child_flag = true;
        }

        else if (input[i] == ')')
        {
            if (stack.get_value() != '(')
            {
                std::cout << "Error!" << std::endl;
                return 2;
            }
            else 
            {
                if (input[i-1] != '(' && input[i-1] != ')')
                {
                    if (right_child_flag)
                        curr_parent = Tree.add_right_child(curr_parent, curr_node_val);
                    else
                        curr_parent = Tree.add_left_child(curr_parent, curr_node_val);
                    right_child_flag = false;
                    curr_node_val = 0;
                }
                stack.pop_front();
                curr_parent = Tree.get_parent(curr_parent);
            }
        }

        else if (input[i] >= '0' && input[i] <= '9')
            curr_node_val = curr_node_val * 10 + input[i]-'0';

        else 
        {
            std::cout << "Error!" << std::endl;
            return 2;
        }
    }
    if (!stack.is_empty())
    {
        std::cout << "Error!" << std::endl;
        return 2;
    }
    return 0;
}