#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include <cctype>
#include <string>
#include <unordered_map>
#include <vector>

#include "AVLTree.h"

// std::string toLower(const std::string& word);
class IndexHandler {
   public:
    // making an instance of avl for each type
    AvlTree<std::string, std::string> wordAVL;
    AvlTree<std::string, std::string> personAVL;
    AvlTree<std::string, std::string> organizationAVL;

    bool isValidString(const std::string& str) {
        return !str.empty();
    }

    void addWord(std::string& word, const std::string& filePath) {  // add word, filepath, and frequency using insert function
        if (!isValidString(word)) {
            cerr << "Cannot add word. Must be a string.";
        }
        toLower(word);
        wordAVL.insert(word, filePath, 1);
        // wordAVL.organize(word);
    }

    void addPerson(std::string& word, const std::string& filePath, size_t freq) {  // if the word already exists, it wont make a new node but it will add the doc and its freq to the map
        if (!isValidString(word)) {
            cerr << "Cannot add Person. Must be a string.";
        }
        toLower(word);
        personAVL.insert(word, filePath, freq);
        // personAVL.organize(word);
    }

    void addOrg(std::string& word, const std::string& filePath, size_t freq) {
        if (!isValidString(word)) {
            cerr << "Cannot add org. Must be a string.";
        }
        toLower(word);
        organizationAVL.insert(word, filePath, freq);
        // organizationAVL.organize(word);
    }

    std::map<std::string, size_t> searchWord(string word) {  // search for word using avl find function, returns map of docs where word is found
        std::string lowercaseWord = toLower(word);
        return wordAVL.find(lowercaseWord);
    }

    std::map<std::string, size_t> searchPerson(string word) {
        std::string lowercaseWord = toLower(word);
        return personAVL.find(lowercaseWord);
    }

    std::map<std::string, size_t> searchOrg(string word) {
        std::string lowercaseWord = toLower(word);
        return organizationAVL.find(lowercaseWord);
    }

    // returns the total unique words in the wordAVL, which will be used in UI
    int uniqueWords() {
        return wordAVL.getTotal();
    }

    std::string& toLower(std::string& word) {  // takes in a word and returns the word lowercased
        for (char& ch: word) {
            ch = tolower(ch);
        }
        return word;
    }
};  // end of index handler class

#endif  // INDEX_HANDLER_H