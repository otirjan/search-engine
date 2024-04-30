#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>

#include "AVLTree.h"

   //std::string toLower(const std::string& word);
class IndexHandler{
    public:
        //making an instance of avl for each type 
        AvlTree<std::string, std::string> wordAVL;    
        AvlTree<std::string, std::string > personAVL;
        AvlTree<std::string, std::string> organizationAVL;

        bool isValidString(const std::string& str) {
        return !str.empty();
    }

        void addWord(std::string word, std::string filePath, size_t freq){   //add word, filepath, and frequency using insert function 
          if (!isValidString(word)) {
            cerr << "Cannot add word. Must be a string.";
        }
           word = toLower(word);
           wordAVL.insert(word, filePath, freq);
           wordAVL.organize(word);
        }

        void addPerson(std::string word, std::string filePath, size_t freq){    //if the word already exists, it wont make a new node but it will add the doc and its freq to the map 
            if (!isValidString(word)) {
            cerr << "Cannot add Person. Must be a string.";
        }
             word = toLower(word);
            personAVL.insert(word, filePath, freq);
            personAVL.organize(word);
        }

        void addOrg(std::string word, std::string filePath, size_t freq){     
            if (!isValidString(word)) {
            cerr << "Cannot add org. Must be a string.";
        }
            word = toLower(word);
            organizationAVL.insert(word, filePath, freq);
            organizationAVL.organize(word);
        }

        std::map<std::string, size_t> searchWord(const string& word){      //search for word using avl find function, returns map of docs where word is found 
            std::string lowercaseWord = toLower(word);
            return wordAVL.find(lowercaseWord);
        }

         std::map<std::string, size_t> searchPerson(const string& word){
            std::string lowercaseWord = toLower(word);
            return personAVL.find(lowercaseWord);
        }

         std::map<std::string, size_t> searchOrg(const string& word){
             std::string lowercaseWord = toLower(word);
            return organizationAVL.find(lowercaseWord);
        }

        //returns the total unique words in the wordAVL, which will be used in UI
        int uniqueWords()
        {
            return wordAVL.getTotal();
        }

        std::string toLower(const std::string& word) { //takes in a word and returns the word lowercased 
        std::string result;
        for (char c : word) {
            result += std::tolower(c);
        }
        return result;
    }
};   //end of index handler class 

#endif // INDEX_HANDLER_H