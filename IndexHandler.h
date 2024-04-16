#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "AVLTree.h"

class IndexHandler{
    private:
        AvlTree<std::string, std::string> wordAVL;    //making an instance of avl for each type 
        AvlTree<std::string, std::map<std::string, std::string>> personAVL;
        AvlTree<std::string, std::map<std::string, std::string>> organizationAVL;
    
    public: 
        void addWord(std::string word, std::string filePath, size_t freq){
           //call insert from avh.h  
        }

        void addPerson(std::string word, std::string filePath, size_t freq){
            
        }

        void addOrg(std::string word, std::string filePath, size_t freq){
            
        }


};   //end of index handler class 


#endif // INDEX_HANDLER_H