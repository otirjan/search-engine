#include "AVLTree.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{

    /*
    * TEST_CASE("testing organize()")
    */

    //intialize an instance of the AvlTree called exampleTree
    AvlTree<std::string,std::string> exampleTree;
    //create the maps that will act as the data for a node
    std::map<size_t, std::string> value1 = {{2, "filepathEx"}, {6, "filepathEx2"}};
    std::map<size_t, std::string> value2 = {{8, "filepathEx3"}, {11, "filepathEx4"}};
    //intsert 2 words into the AvlTree
    exampleTree.insert("hello", value1);
    exampleTree.insert("world", value2);
    //checking if the node with the key "hello" exists inside the AvlTree
    if (exampleTree.contains("hello")) 
    {
        //saving the results of organize() into a variable called organizedMapHello
        auto organizedMapHello = exampleTree.organize("hello");
        std::cout << "Organized map for 'hello':" << std::endl;
        //loop through the organized map
        for (const auto& pair : organizedMapHello) 
        {
            //printing. output: Frequency: 6, Filepath: filepathEx2; Frequency: 2, Filepath: filepathEx. This is now how they were initalized 
            std::cout << "Frequency: " << pair.first << ", Filepath: " << pair.second << std::endl;
        }
    }

    
    /*
    * TEST_CASE("testing first15()")
    */

    //creating a map with 16 test pairs of freqencies and filepaths
    std::map<size_t, std::string> testmap = {{2, "filepathEx"}, {4, "filepathEx2"},{6, "filepathEx2"},{8, "filepathEx2"},{10, "filepathEx2"},{12, "filepathEx2"},{14, "filepathEx2"},{16, "filepathEx2"},{18, "filepathEx2"},{20, "filepathEx2"},{22, "filepathEx2"},{24, "filepathEx2"},{26, "filepathEx2"},{28, "filepathEx2"},{30, "filepathEx2"},{220, "filepathEx2"}};
    //insert new node into exampleTree
    exampleTree.insert("fifteen", testmap);
    //saving the map returned from first15()
     std::map<size_t, std::string> fifteenMap = exampleTree.first15("fifteen");
    //iterating through the map of 15 elements
     for (const auto& pair : fifteenMap)
     {
        //printing the key/value pairs in the map
        std::cout << "Frequency: " << pair.first << ", filepath: " << pair.second << std::endl;
     }

}