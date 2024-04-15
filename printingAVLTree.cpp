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
    std::map<std::string, size_t> value1 = {{"filepathEx", 2}, {"filepathEx2", 6}};
    std::map<std::string, size_t> value2 = {{"filepathEx3", 8}, {"filepathEx4", 11}};
    //insert 2 words into the AvlTree
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
            //printing. output: Filepath:filepathEx2, Frequency: 6; Filepath: filepathEx, Frequency: 2. This is not how they were initalized 
            std::cout << "Filepath: " << pair.first << ", Frequency: " << pair.second << std::endl;
        }
    }

    
    // /*
    // * TEST_CASE("testing first15()")
    // */

    //creating a map with 16 test pairs of freqencies and filepaths; it should NOT print filepathEx, 2 because, once sorted by frequency, that is the smallest freequency
    std::map<std::string, size_t> testmap = {{"filepathEx", 2}, {"filepathEx2", 4},{"filepathEx4", 6},{"filepathEx6", 8},{"filepathEx8", 10},{"filepathEx10", 12},{"filepathEx12", 14},{"filepathEx14", 16},{"filepathEx16", 18},{"filepathEx18", 20},{"filepathEx20", 22},{"filepathEx22", 24},{"filepathEx24", 26},{"filepathEx26", 28},{"filepathEx28", 30},{"filepathEx220", 220}};
    //insert new node into exampleTree
    exampleTree.insert("fifteen", testmap);
    //saving the map returned from first15()
    std::vector<std::pair<std::string, size_t>> fifteenMap = exampleTree.first15("fifteen");
    //iterating through the map of 15 elements
     for (const auto& pair : fifteenMap)
     {
        //printing the key/value pairs in the map
        std::cout << "Filepath: " << pair.first << ", frequency: " << pair.second << std::endl;
     }

}