#include "AVLTree.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{
    AvlTree<std::string,std::string> exampleTree;

    std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}};
    std::map<size_t, std::string> value2 = {{8, "filepathEx3"}, {11, "filepathEx4"}};

    exampleTree.insert("hello", value1);
    exampleTree.insert("world", value2);

    // if (exampleTree.contains("hello"))
    // {
    //     AvlTree<std::string,std::string>::AvlNode* helloNode = exampleTree.find("hello");
    //     if (helloNode != nullptr)
    //     {
    //         // Organize the data for the "hello" node
    //         exampleTree.organize(helloNode);
    //     }
    // }

    if (exampleTree.contains("hello")) 
    {
        auto organizedMapHello = exampleTree.organize("hello");
        std::cout << "Organized map for 'hello':" << std::endl;
        for (const auto& pair : organizedMapHello) 
        {
            std::cout << "Frequency: " << pair.first << ", Filepath: " << pair.second << std::endl;
        }
    }

    exampleTree.prettyPrintTree();
    





}