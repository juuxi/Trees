#include <iostream>
#include "vector.cpp"
#include "Binary_Tree.cpp"

int main()
{
    Binary_Tree<int> Tree;
    Vector<char> input(1);
    char c;
    std::cin >> c;
    for (int i = 0; c != '\n'; i++)
    {
        std::cin >> c;
        input.add(i, c);
    }
    for (int i = 0; i < input.get_size(); i++)
    {
        
    }
    return 0;
}