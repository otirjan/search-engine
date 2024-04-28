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

added:
- uniqueWords() in index handler
- getTitle() in DocParser
- getPublishDate() in DocParser
- getPublications() in DocParser

questions
- collapse parseDoc? u extract things but never use them
- all the words that are parsed go into the word avl yes? even the ones that are also people/orgs? see stats function
- how does "publications" work i don't see that field anywhere in the .json file


*/

class UI
{
    private:
        QueryProcessor queryprocessor;
        IndexHandler handler;
        DocumentParser parser;


    public:
    // default constructor
    UI()
    {
        queryprocessor(IndexHandler());
        IndexHandler handler;
        DocumentParser parser;

    }

    void index()
    {
        std::string userpath;
        std::cout << "Enter directory path: " << std::endl;
        std::cin >> userpath;
        //check with cameron if this is what this function is used for. i think so but idk
        parser.testFileSystem(userpath);

    }

    void indexFromFile()
    {
        //on all 3 trees?
        //i hard coded the csv name. if i have to do all 3 this is a problem yes?

    }

    void query()
    {
        //im putting input into a vector in case there is a "-" i want to preserve it. also bc i want to get all the words in the query
        std::vector<std::string> input;
        std::string line;

        std::cout << "Input query (press enter to finish): " << std::endl;

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

        //with the results i get back from the query processor. these should be filepaths
        std::vector<std::string> final = queryprocessor.getResults();
        //i need to go through the vector
        for (int i = 0; i < final.size(); i++)
        {
            //get the title, date published, publication
            std::cout << "#" << i << " : " << parser.getTitle(final.at(i)) << ", " << parser.getPublishDate(final.at(i)) << ", " << parser.getPublication(final.at(i)) << std::endl;
        }
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
        else
        {
            menu();
        }
    }

    void fullArticle(const std::string& filePath)
    {
        //output the full article 

    }

    void stats()
    {
        //time for indexing
        //time for queries
        //total articles in the current index. if we put EVERY word into the word avl, even words that are people/orgs, then i can increment this value every time we add to wordAVL in the docParser
        //total amount of nodes in the word avl
        int totalUnique = handler.uniqueWords();
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