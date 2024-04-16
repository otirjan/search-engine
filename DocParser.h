#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>

#include <fstream>
#include <sstream>

#include <unordered_set>
#include <vector>

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

#include "porter2_stemmer.h"   //check why this is still swuiggly, i think something needs to be added in the CMAKE but idk what 


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

        string stemWord(string& word){   //just takes in one word, returns that word stemmed

            string stemWord = word;

            Porter2Stemmer::trim(stemWord);
            Porter2Stemmer::stem(stemWord);  

            return stemWord; 
        }


    public: 

        void parseDoc(const string& filePath){
            //go thru and take out stop words, stem words that need it, and exctact info for each document
            

            
            //this goes underneath livs code, where it reads in the document as isw 
            //adding this here, was gonna be in extractInfo but it should be here in the doc parser 
           
           //extract the author from document 
             if (document.HasMember("author") && document["author"].IsString()) {
             string author = document["author"].GetString();
            } else {
            cerr << "Error: json file doesn't contain an author or it is not a string" << endl;
            }

            //extract the publication 
            if (document.HasMember("publication") && document["publication"].IsString()) {
             string author = document["publication"].GetString();
            } else {
            cerr << "Error: json file doesn't contain a publication or it is not a string" << endl;
            }

            //extract people 


            //extract orgs 


        }//end of parsedoc

    void testFileSystem(const string &path)  //this takes in the folder of data and gives us the filepath for each 
    {

    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);

    // loop over all the entries.
    for (const auto &entry : it)
    {

        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            parseDoc(entry.path().string());   //call parsedoc and pass the file path 

        }
    }
}






};//end of doc parser 

