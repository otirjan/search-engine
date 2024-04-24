#ifndef AVL_TREE_H
#define AVL_TREE_H

// #define DEBUG  // Debug macro, uncomment to enable debug mode

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * @class AvlTree
 * @brief This implementation is based on the unbalanced binary search tree and adds hight information
 * to the nodes and a balance function to perform the needed rotations.
 */
template <typename Comparable, typename Value>
class AvlTree
{
private:

    struct AvlNode
    {
        //the word stored in each node
        Comparable key;
        //map that will associate frequency values with filepaths; this is the node's data
        std::map<Value, size_t> data;
        //std::map<size_t, Value, MapComparator> data;
        //pointer to the node's left child
        AvlNode *left;
        //pointer to the node's right child
        AvlNode *right;
        //height of the node, used for balancing
        int height; // Height of the node used for balancing
        //default constructor for an AVL node
        AvlNode(const Comparable& k, const Value& d, const size_t& f)
        {
            key = k;
            data.insert({d, f});
            left = nullptr;
            right = nullptr;
            height = 0;
        }
        //constructor for the clone function/for internal functions
        AvlNode(const Comparable& k, std::map<Value, size_t>& d, AvlNode* l, AvlNode* r, int h)
        : key(k), data(d), left(l), right(r), height(h) {}

    };

    AvlNode *root;

    size_t total = 0;

    // Allowed imbalance in the AVL tree. A higher value will make balancing cheaper
    // but the search less efficient.
    static const int ALLOWED_IMBALANCE = 1;

public:
    // Default constructor
    //edited to also initalized total to 0
    AvlTree() : root{nullptr}, total{0}
    {
    }

    // Rule-of-3 Part 1: Copy constructor
    //edited to set the new tree's total to the old tree's total when the copy constructor is called
    AvlTree(const AvlTree &rhs) : root{nullptr}, total{rhs.total}
    {
        root = clone(rhs.root);
    }

    // Rule-of-3 Part 2: Destructor
    ~AvlTree()
    {
        makeEmpty();
    }

    // Rule-of-3 Part 3: Copy assignment operator
    AvlTree &operator=(const AvlTree &rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
            //modified to set the new tree's total to the old tree's total when the copy assignment operator is called
            total = rhs.total;
        }

        return *this;
    }

    // Move semantics could be implemented here.

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree
     */
    void insert(const Comparable& x,const Value& d, const size_t& f) 
    {
        insert(x, d, f, root);
    }

    /**
    *call to an internal recursive function that locates a given node in the AvlTree and returns the map that constitutes its values
    */
    std::map<Value, size_t> find(const Comparable &x) const
    {
        return find(x, root);
    }

    /*
    *call to an internal recursive function that takes a node's map (its data) and organizes the map from highest frequency to lowest
    */
    std::vector<std::pair<Value, size_t>> organize(const Comparable x) const
    {
        return organize(x, root);
    }

    /*
    *returns the total amount of nodes in the AvlTree
    */
    size_t getTotal() const
    {
        return total;
    }

    /*
    *returns a map that consists of the first 15 keys in a node's data (its map of keys(frequencies) and values(filepaths))
    */
    std::vector<std::pair<Value, size_t>> first15(const Comparable& x) const
    {
        return first15(x, root);
    }

    /*
    *calls internal function to collapse AvlTree into a CSV file
    */
    void exportToCSV() const
    {
        const std::string filename = "AVLTree.csv";
        exportToCSV(filename);
    }

    /*
    *calls function to build AvlTree from a CSV file
    */
    void AVLfromCSV(const std::string& filename) 
    {
        std::ifstream inputFile(filename);

        if(!inputFile.is_open())
        {
            std::cerr << "Error, failed to open file" << filename << std::endl;
            return;
        }

        //store the header
        std::string header;
        std::getline(inputFile, header);

        //while not the end of the file
        while(!inputFile.eof())
        {
            std::string line;
            //while i can get a line
            while (std::getline(inputFile, line))
            {
                //vector to hold it
                std::vector<std::string> tokens;

                //split into tokens based on commas
                std::stringstream ss(line);
                std::string token;
                
                //put all the individual words, split up based on commas, into a vector
                while (std::getline(ss, token, ','))
                {
                    tokens.push_back(token);
                }

                //iterate through the vector
                for (int i = 0; i < tokens.size()-3; i+=2)
                {
                    //call insert. key will be the 1st thing in the vector. doc andd freq needs to increase throughout the vector
                    Comparable key = tokens[i];
                    Value doc = tokens[i+1];
                    size_t freq = std::stoi(tokens[i+2]);
                    insert(key, doc, freq, root);

                }
            }
        }
        //close the file
        inputFile.close();
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance()
    {
        return check_balance(root);
    }
#endif

private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable& x, const Value& document, const size_t& freq, AvlNode *&t)
    //void insert(const Comparable &x, std::map<Value, size_t>& d, AvlNode *&t)
    {
        //if its not found, the word does NOT already exist inside the map
        if (t == nullptr)
        {
            //call the node constructor, give it its key, document and freq into the map
            t = new AvlNode({x, document, freq});
            //increment total
            total++;
            // a single node is always balanced
            return; 
        }

        //potentially add a statement to check. if we find the node and the document matches, increment 

        //recursive call of insert in order to set the node in its place within the tree
        if (x < t->key)
        {
            insert(x, document, freq, t->left);
        }
        else if (t->key < x)
        {
            insert(x, document, freq, t->right);
        }
        else
        {
            // Duplicate; do nothing
            //it ALREADY EXISTS! so, update the node's data by inserting the document and the freq into the node's map
            t->data.insert({document, freq});
        } 

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    /**
     * Internal method to check if x is found in a subtree rooted at t.
     */
    bool contains(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;

        if (x == t->key)
            return true; // Element found.
        else if (x < t->key)
            return contains(x, t->left);
        else
            return contains(x, t->right);
    }

    /**
     * Internal method to check if x is found in a subtree rooted at t.
     */
    std::map<Value, size_t> find (const Comparable &x, AvlNode *t) const
    {
        //if root is null, return an empty map
        if (t == nullptr)
            return std::map<Value, size_t>();
        //if the word is found in the map, return its data
        if (x == t->key)
            return t->data; // Element found.
        //recursive call of find
        else if (x < t->key)
            return find(x, t->left);
        //recursive call of find
        else
            return find(x, t->right);
    }

    /*
    *interal method to sort a node's data from highest frequency to smallest frequency
    */
    std::vector<std::pair<Value, size_t>> organize(const Comparable x, AvlNode *t) const
    {
        //get the node's data using the find function
        std::map<Value, size_t> OGdata = find(x, root);
        //created a vector, organizedData, which is the node's data but in descending order; the keys are still the filepaths
        std::vector<std::pair<Value, size_t>> organizedData(OGdata.begin(), OGdata.end());
        //sort based on frequency
        std::sort(organizedData.begin(), organizedData.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });
        //return the organized vector
        return organizedData;
    }

    /*
    *internal function to return the first 15 key/value pairs in the node's data
    */
    std::vector<std::pair<Value, size_t>> first15(const Comparable& x, AvlNode *t) const
    {
       //retrieve the node's organized data from the organize() function
        std::vector<std::pair<Value, size_t>> nodeData = organize(x, t);
        //intialize an empty vector called results, which will be returned at the end of the function
        std::vector<std::pair<Value, size_t>> results;
        //initalize a variable called count to keep track of the amount of elements im putting into the results  map
        int count = 0;
       //iterate through nodeData (the node's data, a vector of keys(filepaths) and values(frequencies) now sorted greatest to least based on frequencies)
       //if the map doesn't have 15 elements yet, or if nodeData isn't empty (for the ones with less than 15)
        for (auto it = nodeData.begin(); it != nodeData.end() && count < 15; ++it)
        {
            // Put the pair into the results vector
            results.push_back(*it);
            // Increment count
            count++;
        }
       //return the map of 15 (or less) elements
       return results;
    }

    /*
    * internal function to export the Avltree to a csv
    */
    void exportToCSV(const std::string& filename) const
    {
        std::ofstream outputFile(filename);
        //error message

        if(!outputFile.is_open())
        {
            std::cerr << "Error, failed to open file" << filename << std::endl;
            return;
        }
        //print header
        outputFile << "key, filepath, frequency" << std::endl;
        //call inorderTraversal
        inOrderTraversal(root, outputFile);
        //close output file
        outputFile.close();
    }

    /*
    *internal function for in order tree traversal
    */
    void inOrderTraversal(AvlNode *t, std::ofstream& outputFile) const
    {
        //if null, return
        if (t == nullptr)
        {
            return;
        }
        //traverse and print left subtree
        inOrderTraversal(t->left, outputFile);

        //printing
        outputFile << t->key;

        for (const auto& pair : t->data)
        {
            outputFile << "," << pair.first << "," << pair.second;
        }
        outputFile << std::endl;


        //traverse and print right subtree
        inOrderTraversal(t->right, outputFile);
    }

    /*
    *internal function to build an AVL tree from a csv file
    */
    // void AVLfromCSV(const std::string& filename)const
    // {
    //     std::ifstream inputFile(filename);

    //     if(!inputFile.is_open())
    //     {
    //         std::cerr << "Error, failed to open file" << filename << std::endl;
    //         return;
    //     }

    //     //store the header
    //     std::string header;
    //     std::getline(inputFile, header);

    //     //while not the end of the file
    //     while(!inputFile.eof())
    //     {
    //         std::string line;
    //         //while i can get a line
    //         while (std::getline(inputFile, line));
    //         {
    //             //vector to hold it
    //             std::vector<std::string> tokens;

    //             //split into tokens based on commas
    //             std::stringstream ss(line);
    //             std::string token;

    //             //put all the individual words, split up based on commas, into a vector
    //             while (std::getline(ss, token, ','))
    //             {
    //                 tokens.push_back(token);
    //             }
    //             //iterate through the vector
    //             for (int i = 1; i < tokens.size()-1; i+=2)
    //             {
    //                 //call insert. key will be the 1st thing in the vector. doc andd freq needs to increase throughout the vector
    //                 insert(tokens[0], tokens[i+1], std::stoi(tokens[i+2]));
    //             }
    //         }
    //     }
    //     //close the file
    //     inputFile.close();
    // }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        //modified to allow for passing data
        return new AvlNode(t->key, t->data, clone(t->left), clone(t->right), t->height);
    }

    /**
     * Pretty print the tree structure
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        std::cout << prefix;
        // Note: this uses unicode characters for the tree structure. They might not print correctly on
        // all systems (Windows!?!) and all types of output devices.
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Balancing: AVL Rotations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    /**
     * 1. Performs rotations if the the the difference of the height stored in t's two child nodes
     *    more than ALLOWED_IMBALANCE.
     * 2. Updates the height information of the note t.
     *
     * Assumes that the high information in the child nodes is correct. This is guaranteed by calling
     * balance() recursively from the inserted node up to the tree node (see insert()). Rotations will
     * only be performed for node alpha (parent of the parent of the inserted node). For all other nodes,
     * only the height will be updated.
     */
    void balance(AvlNode *&t)
    {
        // special case: empty tree
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
#ifdef DEBUG
        cout << "need to rotateWithLeftChild for node " << k2->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "need to rotateWithRightChild for node " << k1->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
#ifdef DEBUG
        cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

#ifdef DEBUG
    /**
     * Check if the tree is balanced and that the height of the nodes is correct.
     * Throws an exception if the tree is not balanced or the height is wrong.
     * This function is not necessary in production code since the tree is always balanced.
     * It is only compiled when DEBUG is defined.
     */

    int check_balance(AvlNode *node)
    {
        if (node == nullptr)
        {
            return -1;
        }

        // use LRN traversal to check the balance of the tree
        int lHeight = check_balance(node->left) + 1;
        int rHeight = check_balance(node->right) + 1;

        if (std::abs(lHeight - rHeight) > ALLOWED_IMBALANCE)
        {
            throw std::runtime_error("tree is not balanced in node with key " + std::to_string(node->key) + ".");
        }

        int trueNodeHeight = std::max(lHeight, rHeight);

        if (trueNodeHeight != node->height)
        {
            throw std::runtime_error("node does not have correct height value in node with key " + std::to_string(node->key) + ".");
        }

        return trueNodeHeight;
    }
#endif
};

#endif