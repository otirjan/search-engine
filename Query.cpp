#include "Query.h"



//set handler for queryprocessor as the handler from index handler 
QueryProcessor::QueryProcessor(IndexHandler& indHandler) : handler(indHandler){
    //do we need a constructor? i dont think so, just passing in the handler 
}

std::vector<std::string> processQuery(const std::string& query){
    //tokenize, remove stop words, stem words
}