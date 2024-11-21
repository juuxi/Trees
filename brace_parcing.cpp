#include <iostream>
#include <fstream>
#include "Binary_Tree.cpp"
#include "Red_Black_Tree.cpp"

void menu()
{
    std::cout << "1. Удалить узел" << std::endl;
    std::cout << "2. Добавить узел" << std::endl;
    std::cout << "3. Проверить существует ли узел" << std::endl;
    std::cout << "4. Обход дерева в ширину" << std::endl;
    std::cout << "5. Обход дерева в глубину" << std::endl;
    std::cout << "6. Выход" << std::endl;
    std::cout << "> ";
}

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
    Binary_Tree<int> Binary_Tree(root);
    Binary_Tree_node<int>* curr_parent = Binary_Tree.get_root();
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
                    curr_parent = Binary_Tree.add_right_child(curr_parent, curr_node_val);
                else
                    curr_parent = Binary_Tree.add_left_child(curr_parent, curr_node_val);
                right_child_flag = false;
                curr_node_val = 0;
            }
            if (input[i-1] == ')')
            {
                if (!curr_parent->right_child)
                    right_child_flag = true;
                else 
                {
                    std::cout << "Error!" << std::endl;
                    return 2;
                }
            }
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
                        curr_parent = Binary_Tree.add_right_child(curr_parent, curr_node_val);
                    else
                        curr_parent = Binary_Tree.add_left_child(curr_parent, curr_node_val);
                    right_child_flag = false;
                    curr_node_val = 0;
                }
                stack.pop_front();
                curr_parent = Binary_Tree.get_parent(curr_parent);
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
    Vector<int> RB_input(1);
    RB_Tree<int> RB_Tree;
    std::cout << "Центрированный обход бинарного дерева в глубину" << std::endl;
    Binary_Tree.deep_traverse(Binary_Tree.get_root(), RB_input);
    std::cout << std::endl;
    for (int i = 0; i < RB_input.get_size(); i++)
        RB_Tree.add(RB_input[i]);
    std::cout << "Дерево успешно построено" << std::endl;
    char c = '\0';
    while (c != '6')
    {
        menu();
        std::cin >> c;
        std::cout << std::endl;
        switch(c)
        {
            case '1':
            {
                std::cout << "Какой узел вы хотите удалить? ";
                int to_del;
                std::cin >> to_del;
                RB_Tree.delete_node(to_del);
                system("clear");
                break;
            }

            case '2':
            {
                std::cout << "Какой узел вы хотите добавить? ";
                int to_add;
                std::cin >> to_add;
                RB_Tree.add(to_add);
                system("clear");
                break;
            }
                
            case '3':
            {
                std::cout << "Какой узел вы хотите найти? ";
                int to_find;
                std::cin >> to_find;
                RB_Tree_node<int>* curr = RB_Tree.search(nullptr, to_find);
                system("clear");
                if (curr->key == to_find)
                    std::cout << "Узел " << to_find << " есть в дереве" << std::endl;
                else
                    std::cout << "Узла " << to_find << " нет в дереве" << std::endl;
                break;
            }
                
            case '4':
            {
                RB_Tree.breadth_first_search();
                std::cin.ignore();
                std::cout << std::endl << "Нажмите Enter для продолжения ";
                std::cin.ignore();
                system("clear");
                break;
            }

            case '5':
            {
                char dfs_c = '\0';
                std::cout << "1. Прямой обход" << std::endl;
                std::cout << "2. Центрированный обход" << std::endl;
                std::cout << "3. Обратный обход" << std::endl;
                std::cout << "> ";
                std::cin >> dfs_c;
                if (dfs_c == '1')
                    RB_Tree.depth_first_search_forward();
                if (dfs_c == '2')
                    RB_Tree.depth_first_search_central();
                if (dfs_c == '3')
                    RB_Tree.depth_first_search_backward();
                std::cin.ignore();
                std::cout << std::endl << "Нажмите Enter для продолжения ";
                std::cin.ignore();
                system("clear");
                break;
            }
                
            case '6':
                break;
            default:
                break;
        }
    }
    return 0;
}