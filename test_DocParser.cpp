#include "DocParser.h"
#include <iostream>

int main() {
    //  DocumentParser object
    DocumentParser parser;

    // test parsing a single document
    std::string filePath = "sample_data/coll_1/news_0064567.json"; 
    parser.parseDoc(filePath); 

    return 0;
}
