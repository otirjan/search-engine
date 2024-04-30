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


/*
needs to:
- index
- index from file
- query
- view full article
- output time taken for 1 query
- return how many articles are in the index
- any other interesting stats
- a menu




*/

class UI
{
    private:
        DocumentParser parser;
        QueryProcessor queryprocessor;
        IndexHandler handler;
        // DocumentParser parser;
        std::chrono::steady_clock::time_point indexStartTime;
        std::chrono::steady_clock::time_point indexEndTime;
        std::chrono::steady_clock::time_point queryStartTime;
        std::chrono::steady_clock::time_point queryEndTime;


    public:
    // default constructor
    //the handler is the same for the parser and the query processor
    UI() : parser(), queryprocessor(parser.getIndexHandler()) 
    {

    }

    void index()
    {
        indexStartTime = std::chrono::steady_clock::now();
        std::string userpath;
        std::cout << "Enter directory path: " << std::endl;
        std::cin >> userpath;
        //its gonna loop over all the json files in the directory and then parse them all
        parser.testFileSystem(userpath);
        indexEndTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> indexDuration = indexEndTime - indexStartTime;
        std::cout << "Time taken for indexing: " << indexDuration.count() << " seconds" << std::endl;
        //testing purposes
        std::cout << "words in wordAVL: " << queryprocessor.getHandler().uniqueWords() << std::endl;
        std::cout << "articles indexed(should be 3) : " << parser.getCount() << std::endl;
    }

    void indexToFile()
    {
        queryprocessor.getHandler().wordAVL.exportToCSV("wordAVL.csv");
        queryprocessor.getHandler().personAVL.exportToCSV("personAVL.csv");
        queryprocessor.getHandler().organizationAVL.exportToCSV("orgAVL.csv");
    }

    void AVLfromFile()
    {
        queryprocessor.getHandler().wordAVL.AVLfromCSV("wordAVL.csv");
        queryprocessor.getHandler().personAVL.AVLfromCSV("personAVL.csv");
        queryprocessor.getHandler().organizationAVL.AVLfromCSV("orgAVL.csv");
    }

    void query()
    {
        queryStartTime = std::chrono::steady_clock::now();

        //im putting input into a vector in case there is a "-" i want to preserve it. also bc i want to get all the words in the query
        std::vector<std::string> input;
        std::string line;

        std::cout << "Input query (press enter to finish): " << std::endl;

        std::cin >> line;
        //std::getline(std::cin, line);

        std::cout << "this is line: " << line << std::endl;

       //std::getline(std::cin, line);

        //while (std::getline(std::cin, line))
        while (!line.empty())
        {
            //get input until the line is empty ("enter" is pressed)
          //  std::getline(std::cin, line);
           // std::getline(std::cin, line);

            if (line.empty())
            {
                // if (input.empty())
                // {
                //     std::cout << "At least one keyword is required. Please enter a query." << std::endl;
                //     continue;  // Prompt the user to enter a query again
                // }
                // else
                // {
                   // break;
                    continue;
               // }
            }
            std::cout << "hi" << std::endl;
            std::cout << "this is line, grabbed from the user: " << line << std::endl;
            //tokenizes
            // std::istringstream ss(line);
            // std::string word;

            //change to all lowercase

            //puts the input into a vector
            // while (ss >> word)
            // {
            //     input.push_back(word);
            // }

            input.push_back(line);

            for (int i = 0; i < input.size(); i++)
            {
                std::cout << input.at(i) << std::endl;
            }

            std::cout << "this is the end of the vector." << std::endl;

            //trying this?
            line.clear();
           // input.clear();

            //std::getline(std::cin, line);
        }
        std::cout << "testing the vector of input: " << std::endl;
        std::cout << "input size is: " << input.size() << std::endl;
        for (int i = 0; i < input.size(); i++)
        {
            std::cout << input.at(i) << std::endl;
        }
        //call query processor and give it the user input
        queryprocessor.processQuery(input);

        std::cout << "done with process query" << std::endl;
        
        //with the results i get back from the query processor. these should be filepaths
        std::vector<std::string> final = queryprocessor.getResults();
        //i need to go through the vector
        for (long unsigned int i = 0; i < final.size(); i++)
        {
            //get the title, date published, publication
            std::cout << "#" << i << " : " << parser.getTitle(final.at(i)) << ", " << parser.getPublishDate(final.at(i)) << ", " << parser.getPublication(final.at(i)) << std::endl;
        }
        queryEndTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> queryDuration = queryEndTime - queryStartTime;
        std::cout << "Time taken for querying: " << queryDuration.count() << " seconds" << std::endl;

        std::cout << "Would you like to read an article? Y/N" << std::endl;

        char choice;

        std::cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            int selection = 0;
            std::cout << "Which article would you like to read? Enter the article number: " << std::endl;
            std::cin >> selection;
            fullArticle(final.at(selection));
        }
    }

    void fullArticle(const std::string& filePath)
    {
        //output the full article
        std::string fullArticle = parser.fullArticle(filePath);
        std::cout << fullArticle << std::endl; 
    }

    void stats()
    {
        //this value is incremented in DocParser every time we add to the wordAVL
        std::cout << "Total number of individual articles in the current index: " << parser.getCount() << std::endl;
        //total amount of nodes in the word avl
        std::cout << "Total number of unique words indexed: " << queryprocessor.getHandler().uniqueWords() << std::endl;
    }

    void menu()
    {
        while (true)
        {
            std::cout << 
                    "1. Index documents\n"
                     "2. Write index to file\n"
                     "3. Read index from file\n"
                     "4. Query\n"
                     "5. Output statistics\n"
                     "6. Exit\n"
                     "Enter your choice: ";

            int choice = 0;
            std::cin >> choice;

            switch(choice)
            {
                case 1:
                    index();
                    break;
                case 2:
                    indexToFile();
                    break;
                case 3:
                    AVLfromFile();
                    break; 
                case 4:
                    query();
                    break;
                case 5:
                    stats();
                    break;
                case 6:
                    std::cout << "Exiting...." << std::endl;
                    return;
            }
        }
    }
    

};

#endif