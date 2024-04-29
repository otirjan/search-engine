#include "Query.h"
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

void testQueryProcessing1(IndexHandler& indexHandler) {

    std::cout << "Testing query processing...\n";
    QueryProcessor queryProcessor(indexHandler);

    //test 1: should return only one document 
    std::vector<std::string> query = {"german", "business", "trade"};  //should return doc 1 in sample
    queryProcessor.processQuery(query);
    std::vector<std::string> results = queryProcessor.getResults();
    std::cout << "Search results:\n";
    for (const auto& result : results) {
        std::cout << result << std::endl;
        if(result.empty()){
            cout<<"results are empty";
        }
    } //PASSED  (should return 4567)
    
}

void testQueryProcessing2(IndexHandler& indexHandler) {
    //test 2: query with stop words: should return same as test 1
     QueryProcessor queryProcessor(indexHandler);
    
    std::vector<std::string> stopWordsquery = {"the","german", "have", "business","trade"};  //should return doc 1 in sample
    queryProcessor.processQuery(stopWordsquery);
    std::vector<std::string> stopWordresults = queryProcessor.getResults();
    std::cout << "Search results:\n";
    for (const auto& result : stopWordresults) {
        std::cout << result << std::endl;
        if(result.empty()){
            cout<<"results are empty";
        }
    }  //PASSED (returns 4567)
}


//THIS TEST IS FAILING, whyyy, something wrong with negation in query.cpp
void testQueryProcessing3(IndexHandler& indexHandler) {
     //test 3: query with - words, should return nothing even tho german is present in the doc 
     QueryProcessor queryProcessor(indexHandler);
    
     std::vector<std::string> minusWordsquery = {"german","-businesses"};  //should return doc 1 in sample
     queryProcessor.processQuery(minusWordsquery);
     std::vector<std::string> minusWordsResults = queryProcessor.getResults();
     std::cout << "Search results:\n";
    for (const auto& result : minusWordsResults) {
        std::cout << result << std::endl;   //should be empty
    }
    if(minusWordsResults.empty()){
            cout<<"results are empty";
        }
} //PASSEDDD

void testQueryProcessing4(IndexHandler& indexHandler) { 
    QueryProcessor queryProcessor(indexHandler);
    std::vector<std::string> singleWordQuery = {"coverage"};
    queryProcessor.processQuery(singleWordQuery);
    std::vector<std::string> singleWordResults = queryProcessor.getResults();
    std::cout << "Search results with single word query:\n";
    for (const auto& result : singleWordResults) {
        std::cout << result << std::endl;  //should be 4568 
    }
    if(singleWordResults.empty()){
            cout<<"results are empty";
        }
} //PASSED

void testQueryProcessing5(IndexHandler& indexHandler) { 
    QueryProcessor queryProcessor(indexHandler);
    std::vector<std::string> uncommonWordQuery = {"unicorns"};
    queryProcessor.processQuery(uncommonWordQuery);
    std::vector<std::string> uncommonWordResults = queryProcessor.getResults();
    std::cout << "Search results with uncommon word query:\n";
    for (const auto& result : uncommonWordResults) {
        std::cout << result << std::endl;  //should have no resutls from this dataset 
    }
    if(uncommonWordResults.empty()){
            cout<<"results are empty";
        }
}//PASSED 






int main() {
    // Path to the folder containing the data
    std::string dataFolderPath = "sample_data/coll_1";

    // Create an instance of DocumentParser
    DocumentParser docParser;

    // Call the function to parse documents in the specified folder
    docParser.testFileSystem(dataFolderPath);

    IndexHandler handler;
    handler = docParser.getIndexHandler();

    std::cout << "Parsing complete." << std::endl;

   //test one of these at a time for convenience
   
    //testQueryProcessing1(handler);      //(should return 4567)
    //testQueryProcessing2(handler);    //should return 4567 
    //testQueryProcessing3(handler);     //should return empty 
    //testQueryProcessing4(handler);     //should be 4568
    //testQueryProcessing5(handler);     //should be empty


    return 0;
}
