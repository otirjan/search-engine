#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <iostream>
#include <chrono>
#include "AVLTree.h"
#include "DocParser.h"
#include "IndexHandler.h"
#include "Query.h"
#include <vector>
#include <sstream>
#include <cctype>

class UI
{
    private:
        //instance of the DocumentParser class called parser, to be used in the UI's internal functions
        DocumentParser parser;
        //instance of the QueryProcessor class called queryprocessor, to be used in the UI's internal functions
        QueryProcessor queryprocessor;
        //variable for keeping track of time, to be used in the UI's internal functions
        std::chrono::steady_clock::time_point indexStartTime;
        //variable for keeping track of time, to be used in the UI's internal functions
        std::chrono::steady_clock::time_point indexEndTime;
        //variable for keeping track of time, to be used in the UI's internal functions
        std::chrono::steady_clock::time_point queryStartTime;
        //variable for keeping track of time, to be used in the UI's internal functions
        std::chrono::steady_clock::time_point queryEndTime;


    public:
    // default constructor
    //the handler is the same for the parser and the query processor
    UI() : parser(), queryprocessor(parser.getIndexHandler()) 
    {

    }


    //creates an index from a file directory. parameter is for a prompt from the command line interface
    void index(const std::string& filepath)
    {
        //starts time
        indexStartTime = std::chrono::steady_clock::now();
        //calls the parser's testFileSystem function, which loops over all the json files in the directory and parses them all
        parser.testFileSystem(filepath);
        //ends time
        indexEndTime = std::chrono::steady_clock::now();
        //calculates the time passed
        std::chrono::duration<double> indexDuration = indexEndTime - indexStartTime;
        //prints the time spent making an index
        std::cout << "Time taken for indexing: " << indexDuration.count() << " seconds" << std::endl;
        indexToFile();
    }

    //creates an index from a file directory. this index is called by the menu
    void index()
    {
        //string variable called userpath
        std::string userpath;
        //prompts user for the directory path
        std::cout << "Enter directory path: " << std::endl;
        //accepts user input
        std::cin >> userpath;
        //starts time
        indexStartTime = std::chrono::steady_clock::now();
        //calls the parser's testFileSystem function, which loops over all the json files in the directory and parses them all
        parser.testFileSystem(userpath);
        //ends time
        indexEndTime = std::chrono::steady_clock::now();
        //calculates the time passed
        std::chrono::duration<double> indexDuration = indexEndTime - indexStartTime;
        //prints the time spent making an index
        std::cout << "Time taken for indexing: " << indexDuration.count() << " seconds" << std::endl;
    }

    //writes an AVLTree(index) to a csv file
    void indexToFile()
    {
        //using the handler, calls AvlTree's exportToCSV function and passes in corresponding file names; fills wordAVL.csv
        queryprocessor.getHandler().wordAVL.exportToCSV("wordAVL.csv");
        //using the handler, calls AvlTree's exportToCSV function and passes in corresponding file names; fills personAVL.csv
        queryprocessor.getHandler().personAVL.exportToCSV("personAVL.csv");
        //using the handler, calls AvlTree's exportToCSV function and passes in corresponding file names; fills orgAVL.csv
        queryprocessor.getHandler().organizationAVL.exportToCSV("orgAVL.csv");
    }

    //creates an Avltree(index) from a csv file
    void AVLfromFile()
    {
        //using the handler, calls AvlTree's AVLfromCSV function and passes in corresponding file names; fills wordAVL
        queryprocessor.getHandler().wordAVL.AVLfromCSV("wordAVL.csv");
        //using the handler, calls AvlTree's AVLfromCSV function and passes in corresponding file names; fills personAVL
        queryprocessor.getHandler().personAVL.AVLfromCSV("personAVL.csv");
        //using the handler, calls AvlTree's AVLfromCSV function and passes in corresponding file names; fills orgAVL
        queryprocessor.getHandler().organizationAVL.AVLfromCSV("orgAVL.csv");
    }


    //allows user to search the index. parameter is for a prompt from the command line interface
    void query(const std::string& query)
    {
        //starts time
        queryStartTime = std::chrono::steady_clock::now();

        //initalizes a vector of strings called input, which will hold user input
        std::vector<std::string> input;

        // Create a string stream to tokenize the query
        std::istringstream iss(query);
        std::string word;

        // Tokenize the query and add each word to the input vector
        while (iss >> word)
        {
            input.push_back(word);
        }

        std::cout << "input vector: " << std::endl;

        for (long unsigned int i =0; i < input.size(); i++)
        {
            std::cout << input.at(i) << ", ";
        }
        std::cout << endl;

        //call query processor and gives it the user input
        queryprocessor.processQuery(input);

        //create a vector of strings with the results returned from the query processor; these strings are filepaths
        std::vector<std::string> final = queryprocessor.getResults();

        //if this vector is empty, no results were found; exit function
        if (final.size() == 0)
        {
            //alerts users that no articles matched their query
            std::cout << "no results found" << std::endl;
            //exits back to menu
            return;
        }

        //iterates through the vector of filepaths and prints the results of the query to the terminal
        for (long unsigned int i = 0; i < final.size(); i++)
        {
            //prints the number, article title, date published, and publication
            std::cout << " # " << i << ": " << parser.getTitle(final.at(i)) << ", " << parser.getPublishDate(final.at(i)) << ", " << parser.getPublication(final.at(i)) << std::endl;
        }

        //stops time
        queryEndTime = std::chrono::steady_clock::now();
        //calculates elapsed time
        std::chrono::duration<double> queryDuration = queryEndTime - queryStartTime;
        //prints elapsed time to the terminal
        std::cout << "Time taken for querying: " << queryDuration.count() << " seconds" << std::endl;

        //gives the user an option to read the full text of an article returned as a result of their query
        std::cout << "Would you like to read an article? Y/N" << std::endl;
        //variable of type ch called choice
        char choice;
        //retrieves the user's input
        std::cin >> choice;
        //if the user indicates yes
        if (choice == 'Y' || choice == 'y')
        {
            //int variable called selection initalized to 0
            int selection = 0;
            //asks the user to specify which article they would like to read the full test of
            std::cout << "Which article would you like to read? Enter the number(#) that corresponds to the article's position in the results list: " << std::endl;
            //retrieves user's selection
            std::cin >> selection;
            //calls UI's fullArticle function, passes it corresponding filepath from the final vector
            fullArticle(final.at(selection));
        }
    }

    //allows user to search the index
    void query()
    {
        //initalizes a vector of strings called input, which will hold user input
        std::vector<std::string> input;
        //initalizes a string variable called line
        std::string line;

        //prompts the user for their query
        std::cout << "Input query (press enter to finish): " << std::endl;

        //reads in the user's query
        std::getline(std::cin, line);
        std::getline(std::cin, line);

        //starts time
        queryStartTime = std::chrono::steady_clock::now();

        //while the query has not been processed (meaning the string is not empty)
        while (!line.empty())
        {
            ////split the query into tokens
            std::istringstream iss(line);
            std::string word;

            //read each word from the stringstream and add it to the input vector
            while (iss >> word)
            {
                input.push_back(word);
            }

            //clears the line/query
            line.clear();
        }

        //call query processor and gives it the user input
        queryprocessor.processQuery(input);

        //create a vector of strings with the results returned from the query processor; these strings are filepaths
        std::vector<std::string> final = queryprocessor.getResults();

        //if this vector is empty, no results were found; exit function
        if (final.size() == 0)
        {
            //alerts users that no articles matched their query
            std::cout << "no results found" << std::endl;
            //exits back to menu
            return;
        }

        //iterates through the vector of filepaths and prints the results of the query to the terminal
        for (long unsigned int i = 0; i < final.size(); i++)
        {
            //prints the number, article title, date published, and publication
            std::cout << " # " << i << ": " << parser.getTitle(final.at(i)) << ", " << parser.getPublishDate(final.at(i)) << ", " << parser.getPublication(final.at(i)) << std::endl;
        }

        //stops time
        queryEndTime = std::chrono::steady_clock::now();
        //calculates elapsed time
        std::chrono::duration<double> queryDuration = queryEndTime - queryStartTime;
        //prints elapsed time to the terminal
        std::cout << "Time taken for querying: " << queryDuration.count() << " seconds" << std::endl;

        //gives the user an option to read the full text of an article returned as a result of their query
        std::cout << "Would you like to read an article? Y/N" << std::endl;
        //variable of type ch called choice
        char choice;
        //retrieves the user's input
        std::cin >> choice;
        //if the user indicates yes
        if (choice == 'Y' || choice == 'y')
        {
            //int variable called selection initalized to 0
            int selection = 0;
            //asks the user to specify which article they would like to read the full test of
            std::cout << "Which article would you like to read? Enter the number(#) that corresponds to the article's position in the results list: " << std::endl;
            //retrieves user's selection
            std::cin >> selection;
            //calls UI's fullArticle function, passes it corresponding filepath from the final vector
            fullArticle(final.at(selection));
        }
    }

    /*
    * prints the full text of a given article
    * const std::string& filePath: the path to a given article
    */
    void fullArticle(const std::string& filePath)
    {
        //creates a string variable called fullArticle and sets it equal to the string returned from the parser's fullArticle function
        std::string fullArticle = parser.fullArticle(filePath);
        //prints string to terminal
        std::cout << fullArticle << std::endl; 
    }

    //prints interesting statistics about the program to the terminal
    void stats()
    {
        //prints the amount of articles in the index; this value is incremented in DocParser every time we add to the wordAVL
        std::cout << "Total number of individual articles in the current index: " << parser.getCount() << std::endl;
        //prints the total amount of nodes in the word avl
        std::cout << "Total number of unique words indexed: " << queryprocessor.getHandler().uniqueWords() << std::endl;
    }

    //a menu which accesses all the UI functions; runs until the user terminates
    void menu()
    {
        //while the loop is true
        while (true)
        {
            //prints menu options
            std::cout << 
                    "1. Index documents\n"
                     "2. Write index to file\n"
                     "3. Read index from file\n"
                     "4. Query\n"
                     "5. Output statistics\n"
                     "6. Exit\n"
                     "Enter your choice: ";
            //int variable choice initalized to 0
            int choice = 0;
            //retrieves the user's input and stores the answer in the choice variable
            std::cin >> choice;

            if (std::cin.fail()) { //since cin is expecting an int, if its not an int it will fail
                std::cout<<"Error: Please enter a valid choice! Must enter number 1-6." << std::endl;
                std::cin.clear(); //clear cin so a valid number can be entered 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // get rid of input buffer
                continue;   //let user enter a num 
            }
          
            //calls the corresponding function according to the value of choice
            switch(choice)
            {
                //creates a index from a file directory
                case 1:
                    index();
                    break;
                //collapses an Avltree(index) into a csv file
                case 2:
                    indexToFile();
                    break;
                //creates an AvlTree(index) from a csv file
                case 3:
                    AVLfromFile();
                    break; 
                //performs a query
                case 4:
                    query();
                    break;
                //prints interesting statistics to terminal
                case 5:
                    stats();
                    break;
                //terminates
                case 6:
                    std::cout << "Exiting...." << std::endl;
                    return;
            }
        }
    }
};

#endif