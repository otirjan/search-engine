#include "Query.h"
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

//VERY TENTATIVE, QUERY NOT WORKING 100% BUT SOMETHINGS WORKING!!!

void testQueryProcessing(IndexHandler& indexHandler) {

    std::cout << "Testing query processing...\n";
    QueryProcessor queryProcessor(indexHandler);

    // Add test cases for query processing using real index data
    std::vector<std::string> query = {"equity", "interest"};  //should return doc 1
    queryProcessor.processQuery(query);
    std::vector<std::string> results = queryProcessor.getResults();
    std::cout << "Search results:\n";
    for (const auto& result : results) {
        std::cout << result << std::endl;
        if(result.empty()){
            cout<<"results are empty";
        }
    }
    // Add assertions to validate the results
}




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

    testQueryProcessing(handler);

    return 0;
}
