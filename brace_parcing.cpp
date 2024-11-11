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
    Binary_Tree<int> Tree(root);
    int curr_node_val = 0;
    for (int i = 0; i < input.size(); i++)
    {
        
    }
    return 0;
}