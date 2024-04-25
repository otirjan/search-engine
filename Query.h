#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <map>
#include "IndexHandler.h"
#include "DocParser.h"

        class QueryProcessor{
            public:
                //take in the users string, breaks it into what terms are people/orgs/words, gets results from avl trees, ranks them on relevancy
                //take same index handler u used for doc parser, acsess to the same data 
                QueryProcessor(IndexHandler& handler); 
               
               //take in the query, return a list of documents 
                std::vector<std::string> processQuery(const std::string& query);

            private:
                IndexHandler& handler;

        };

#endif