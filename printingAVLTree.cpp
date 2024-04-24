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
    //insert 2 words into the AvlTree
    exampleTree.insert("hello", "filepathEx", 2);
    exampleTree.insert("hello", "filepathEx2", 6);
    exampleTree.insert("world", "filepathEx3", 8);
    exampleTree.insert("world", "filepathEx4", 1);
    //checking if the node with the key "hello" exists inside the AvlTree
    if (exampleTree.contains("hello")) 
    {
        //saving the results of organize() into a variable called organizedMapHello
        auto organizedMapHello = exampleTree.organize("hello");
        std::cout << "Organized map for 'hello':" << std::endl;
        //loop through the organized map
        for (const auto& pair : organizedMapHello) 
        {
            //printing. output: Filepath:filepathEx2, Frequency: 6; Filepath: filepathEx, Frequency: 2. This is not how they were initalized 
            std::cout << "Filepath: " << pair.first << ", Frequency: " << pair.second << std::endl;
        }
    }





    
     /*
     * TEST_CASE("testing first15() with 16 values")
     */

    //insert new node into exampleTree. should NOT print filepathEx, 2 because, once sorted by frequency, that is the smallest freequency
    exampleTree.insert("fifteen","filepathEx", 2);
    exampleTree.insert("fifteen", "filepathEx2", 4);
    exampleTree.insert("fifteen", "filepathEx4", 6);
    exampleTree.insert("fifteen", "filepathEx6", 8);
    exampleTree.insert("fifteen", "filepathEx8", 10);
    exampleTree.insert("fifteen", "filepathEx10", 12);
    exampleTree.insert("fifteen", "filepathEx12", 14);
    exampleTree.insert("fifteen", "filepathEx14", 16);
    exampleTree.insert("fifteen", "filepathEx16", 18);
    exampleTree.insert("fifteen", "filepathEx18", 20);
    exampleTree.insert("fifteen", "filepathEx20", 22);
    exampleTree.insert("fifteen", "filepathEx22", 24);
    exampleTree.insert("fifteen", "filepathEx24", 26);
    exampleTree.insert("fifteen", "filepathEx26", 28);
    exampleTree.insert("fifteen", "filepathEx28", 30);
    exampleTree.insert("fifteen", "filepathEx220", 220);

    //saving the map returned from first15()
    std::vector<std::pair<std::string, size_t>> fifteenMap = exampleTree.first15("fifteen");
    //iterating through the map of 15 elements
    for (const auto& pair : fifteenMap)
    {
        //printing the key/value pairs in the map
        std::cout << "Filepath: " << pair.first << ", frequency: " << pair.second << std::endl;
    }


    




    /*
    TEST_CASE("testing first15() with 14 values")
    */

    //creating a map with 14 values
    exampleTree.insert("fourteen","filepathEx", 2);
    exampleTree.insert("fourteen", "filepathEx2", 4);
    exampleTree.insert("fourteen", "filepathEx4", 6);
    exampleTree.insert("fourteen", "filepathEx6", 8);
    exampleTree.insert("fourteen", "filepathEx8", 10);
    exampleTree.insert("fourteen", "filepathEx10", 12);
    exampleTree.insert("fourteen", "filepathEx12", 14);
    exampleTree.insert("fourteen", "filepathEx14", 16);
    exampleTree.insert("fourteen", "filepathEx16", 18);
    exampleTree.insert("fourteen", "filepathEx18", 20);
    exampleTree.insert("fourteen", "filepathEx20", 22);
    exampleTree.insert("fourteen", "filepathEx22", 24);
    exampleTree.insert("fourteen", "filepathEx24", 26);
    exampleTree.insert("fourteen", "filepathEx26", 28);

    //saving the map returned from first15()
    std::vector<std::pair<std::string, size_t>> fourteenMap = exampleTree.first15("fourteen");
    //iterating through the map of 15 elements
    for (const auto& pair : fourteenMap)
    {
        //printing the key/value pairs in the map
        std::cout << "Filepath: " << pair.first << ", frequency: " << pair.second << std::endl;
    }




}