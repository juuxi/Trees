#include <iostream>
#include "Binary_Tree.cpp"

int main()
{
    std::string input;
    getline(std::cin, input);
    if (input[0] != '(')
    {
        std::cout << "Error!" << std::endl;
        return 1;
    }
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
    for (int i = 0; i < input.size(); i++)
    {
        
    }
    return 0;
}