#include <iostream>
#include "DocParser.h"
#include "userinterface.h"
#include "Query.h"
#include "IndexHandler.h"
#include "AVLTree.h"
#include <chrono>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>


using namespace std;

int main(int argc, char* argv[])
{
    //create an instance of the UI class
    UI search;

    //create a string variable to read in the command from the command line interface
    std::string command = argv[1];

    //intializes string variables filepath and query_string to hold input from terminal
    std::string filepath;
    std::string query_string;

    //if the command is index
    if (command == "index")
    {
        //saves the filepath
        filepath = argv[2];
        //calls UI's index function that accepts a string parameter
        search.index(filepath);
    }
    //if the command is query
    if (command == "query")
    {
        //saves the query terms
        query_string = argv[2];
        //constructs index from csv files
        search.AVLfromFile();
        //calls UI's query function that accepts a string parameter
        search.query(query_string);
    }
    //if the command is ui
    if (command == "ui")
    {
        //calls UI's menu, which allows the user to index, collapse to csv, build from csv, query, view an article and view stats at their leisure
        search.menu();
    }

    return 0;
}

