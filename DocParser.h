
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

#include "porter2_stemmer.h"   //check why this is still swuiggly, i think something needs to be added in the CMAKE but idk what 
#include "IndexHandler.h"

using namespace rapidjson;
using namespace std;

// void testReadJsonFile(const string &fileName);
// void testFileSystem(const string &path);   idk what these are i think supposed to read in from file 


class DocumentParser {
    private:
        set<string> stopwords;
        IndexHandler handler;

    public:

        DocumentParser();
        vector <string> tokenize (const string& text);
        string stemWord(string& word);
        void parseDoc(const string& filePath);
        size_t calcFrequency(const Document& document, const string& word);
        void testFileSystem(const string &path);  
        void initializeStopWords();
        IndexHandler& getIndexHandler();
        string getTitle(const string& filePath);
        string getPublishDate(const string& filePath);
        string getPublication(const string& filePath);


};//end of doc parser 

#endif

