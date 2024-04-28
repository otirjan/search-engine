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
        QueryProcessor queryprocessor;


    public:
    // default constructor
    UI()
    {
        queryprocessor(IndexHandler());

    }

    void index()
    {

    }

    void indexFromFile()
    {

    }

    void query()
    {
        //im putting input into a vector in case there is a "-" i want to preserve it. also bc i want to get all the words in the query
        std::vector<std::string> input;
        std::string line;

        std::cout << "input query (press enter to finish): " << std::endl;

        while(true)
        {
            //get input until the line is empty ("enter" is pressed)
            std::getline(std::cin, line);

            if (line.empty())
            {
                break;
            }
            //tokenizes
            std::istringstream ss(line);
            std::string word;
            //puts the input into a vector
            while (ss >> word)
            {
                input.push_back(word);
            }
        }
        //call query processor and give it the user input
        queryprocessor.processQuery(input);
    }

    void fullArticle()
    {

    }

    void time()
    {
        //time for indexing and for queries

    }

    void totalArticles()
    {

    }

    void stats()
    {
        //unique words

    }

    void menu()
    {
        while (true)
        {
            std::cout << 
            "1. Index documents\n"
                     "2. Read index from file\n"
                     "3. Query\n"
                     "4. View full article\n"
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
                    indexFromFile();
                    break;
                case 3:
                    query();
                    break;
                case 4:
                    fullArticle();
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