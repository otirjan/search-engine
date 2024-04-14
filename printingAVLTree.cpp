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

    // if (exampleTree.contains("hello")) 
    // {
    //     auto organizedMapHello = exampleTree.organize("hello");
    //     std::cout << "Organized map for 'hello':" << std::endl;
    //     for (const auto& pair : organizedMapHello) 
    //     {
    //         std::cout << "Frequency: " << pair.first << ", Filepath: " << pair.second << std::endl;
    //     }
    // }

    // exampleTree.prettyPrintTree();

    //function that prints the first 15 elements in a node's map
    
    
    
    //test map with 16 values
    std::map<size_t, std::string> testmap = {{2, "filepathEx"}, {4, "filepathEx2"},{6, "filepathEx2"},{8, "filepathEx2"},{10, "filepathEx2"},{12, "filepathEx2"},{14, "filepathEx2"},{16, "filepathEx2"},{18, "filepathEx2"},{20, "filepathEx2"},{22, "filepathEx2"},{24, "filepathEx2"},{26, "filepathEx2"},{28, "filepathEx2"},{30, "filepathEx2"},{220, "filepathEx2"}};
    exampleTree.insert("fifteen", testmap);
    std::map<size_t, std::string> fifteenMap = exampleTree.first15("fifteen");
    for (const auto& pair : fifteenMap)
    {
        std::cout << "Frequency: " << pair.first << ", filepath: " << pair.second << std::endl;
    }




    




}