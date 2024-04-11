#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <unordered_set>
#include <vector>

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "porter2_stemmer.h"

using namespace rapidjson;
using namespace std;

// void testReadJsonFile(const string &fileName);
// void testFileSystem(const string &path);   idk what these are i think supposed to read in from file 

class DocumentParser {
    private:
        unordered_set<string> stopWords = {"a", "an", "are", "as", "at", "be", "but", "by", "for", "if", "if", "in", "into", "is", "it", "no", "not", "of", "on", "or", "such", "that", "the", "their", "then", "there", "they", "this", "to", "was", "will", "with"};

        vector <string> tokenize (const string& str){
            std::vector<std::string> tokens;   //create a vector of tokens with words from the doc
                //logic for tokenizing
            return tokens;
        }

        void removeStopWords(vector<string>& tokens){
            //look at each token, if its one of the stop words, take it out 
        }

        string stemWord(string& word){
            //implement logic to stem the word
            Porter2Stemmer::trim(to_stem);
            Porter2Stemmer::stem(to_stem);   //we need these to stem words 
            return word; 
        }

        void extractInfo(const string& filePath){   
            //take in the doc file path, go thru text, extract author, publication
        }


    public: 

        void parseDoc(const string& filePath){
            //go thru and take out stop words, stem words that need it, and exctact info for each document
        }







}//end of doc parser 
