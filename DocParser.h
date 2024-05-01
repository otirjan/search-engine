#ifndef DOC_PARSER_H
#define DOC_PARSER_H

#include <iostream>
#include <filesystem>
#include <iomanip>

#include <fstream>
#include <sstream>

#include <unordered_set>

#include <set>
#include <sstream>
#include <algorithm>

#include <vector>

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

#include "IndexHandler.h"

using namespace rapidjson;
using namespace std;

class DocumentParser {
    private:
        std::unordered_set<string> stopwords;
        IndexHandler handler;
        int count;

    public:
        DocumentParser();
        vector <string> tokenize (const string& text);
        void parseDoc(const string& filePath);
        size_t calcFrequency(const Document& document, const string& word);
        void testFileSystem(const string &path);  
        void initializeStopWords();
        IndexHandler& getIndexHandler();
        string getTitle(const string& filePath);
        string getPublishDate(const string& filePath);
        string getPublication(const string& filePath);
        string fullArticle(const string& filePath);
        int getCount();


};//end of doc parser 

#endif

