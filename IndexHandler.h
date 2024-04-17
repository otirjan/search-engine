#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "AVLTree.h"

class IndexHandler{
    private:
        AvlTree<std::string, std::string> wordAVL;    //making an instance of avl for each type 
        AvlTree<std::string, std::string > personAVL;
        AvlTree<std::string, std::string> organizationAVL;
    
    public: 
        void addWord(std::string word, std::string filePath, size_t freq){   //add word, filepath, and frequency using insert function 
           wordAVL.insert(word, filePath, freq);
        }

        void addPerson(std::string word, std::string filePath, size_t freq){    //if the word already exists, it wont make a new node but it will add the doc and its freq to the map 
            personAVL.insert(word, filePath, freq);
        }

        void addOrg(std::string word, std::string filePath, size_t freq){     
            organizationAVL.insert(word, filePath, freq);
        }

        std::map<std::string, size_t> searchWord(const string& word){      //search for word using avl find function, returns map of docs where word is found 
            return wordAVL.find(word);
        }

         std::map<std::string, size_t> searchPerson(const string& word){
            return personAVL.find(word);
        }

         std::map<std::string, size_t> searchOrg(const string& word){
            return organizationAVL.find(word);
        }




};   //end of index handler class 


#endif // INDEX_HANDLER_H