#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "IndexHandler.h"
#include "DocParser.h"

        class QueryProcessor{
            private:
                IndexHandler& handler;
                set<string> stopwords;
            
            public:
                //take in the users string, breaks it into what terms are people/orgs/words, gets results from avl trees, ranks them on relevancy
                QueryProcessor(IndexHandler& handler); 
               
               //take in the query, return a list of documents 
                std::vector<std::string> processQuery(const std::string& query);

                std::vector<std::string> tokenize (const std::string& text);
                std::string stemWord(std::string& word);
                void initializeStopWords();

                //take in the processed query, search for the words in the AVL trees, call rank results to rank 
                void searchQuery(std::string& query);

                std::vector<std::string> rankResults (std::map<std::string, size_t>& firstDocs,std::vector<std::string>& remainingTerms);

        };

#endif