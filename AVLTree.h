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

    //struct for the nodes in the AVL tree, private, belongs to the AVL tree
    struct AvlNode
    {
        //the word stored in each node
        Comparable key;
        //map that will associate frequency values with filepaths; this is the node's data
        std::map<Value, size_t> data;
        //pointer to the node's left child
        AvlNode *left;
        //pointer to the node's right child
        AvlNode *right;
        //height of the node, used for balancing
        int height;
        //default constructor for an AVL node
        AvlNode(const Comparable& k, const Value& d, const size_t& f)
        {
            //sets key equal to the word passed into the constructor
            key = k;
            //insert the filepath and frequency into the node's data map
            data.insert({d, f});
            //set left pointer to null
            left = nullptr;
            //set right pointer to null
            right = nullptr;
            //initalize height as 0
            height = 0;
        }
        //constructor for the clone function/for internal functions
        AvlNode(const Comparable& k, std::map<Value, size_t>& d, AvlNode* l, AvlNode* r, int h)
        : key(k), data(d), left(l), right(r), height(h) {}

    };

    //intialize the AVLTree's root node to nullptr
    AvlNode *root = nullptr;
    //variable that keeps track of the amount of nodes in the AVLTree; intialize to 0
    size_t total = 0;

    // Allowed imbalance in the AVL tree. A higher value will make balancing cheaper
    // but the search less efficient.
    static const int ALLOWED_IMBALANCE = 1;

public:
    /*
    *default constructor for an AvlTree
    *root: "base" of Avl tree structure; set to nullptr
    *total: size_t keeping track of the amount of nodes in the Avl Tree, initalized as 0
    */
    AvlTree() : root{nullptr}, total{0}
    {
    }

    // Rule-of-3 Part 1: Copy constructor
    /*
    *copy constructor for an AvlTree
    *root: "base" of Avl tree structure; set to nullptr
    *total: size_t keeping track of the amount of nodes in the Avl Tree; set to the same value as rhs
    */
    AvlTree(const AvlTree &rhs) : root{nullptr}, total{rhs.total}
    {
        //clones AVL tree starting from rhs's root node
        root = clone(rhs.root);
    }

    // Rule-of-3 Part 2: Destructor
    ~AvlTree()
    {
        //empties AVL tree
        makeEmpty();
    }

    /*
    *copy assignment operator
    *const Avltree& rhs: reference to an Avl tree that will be copied
    */
    AvlTree &operator=(const AvlTree &rhs)
    {
        //if the trees are not the same
        if (this != &rhs)
        {
            makeEmpty();
            //clone the tree starting with the root
            root = clone(rhs.root);
            //set the total equal to rhs's total
            total = rhs.total;
        }
        //return AVl tree object
        return *this;
    }

    /**
     * public function that calls private AVL Tree function contains; returns true if x is found in the tree.
     * const Comparable& x: the key of a node (a word)
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
     * public function that calls private AVL tree function insert function; inserts x into the AVL Tree
     * const Comparable& x: the key of a node (a word)
     * const Value& d: filepath to a given article
     * const size_t& f: frequency associated with a given article
     */
    void insert(const Comparable& x,const Value& d, const size_t& f) 
    {
        insert(x, d, f, root);
    }

    /**
    *call to an internal recursive function that locates a given node in the AvlTree and returns the map that constitutes its values
    *const Comparable& x:  the key of a node (a word)
    */
    std::map<Value, size_t> find(const Comparable &x) const
    {
        return find(x, root);
    }

    /*
    *call to an internal recursive function that takes a node's map (its data) and organizes the map from highest frequency to lowest
    *const Comparable& x: the key of a node(a word)
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
    *returns a map that consists of the first 15 keys in a node's data (its map of keys(filepaths) and values(frequencies))
    *const Comparable& x: the key of a node(a word)
    */
    std::vector<std::pair<Value, size_t>> first15(const Comparable& x) const
    {
        return first15(x, root);
    }

    /*
    *public AvlTree function to collapse AvlTree into a CSV file
    *const std::string& filename: the name the file which the AvlTree will be written to
    */
    void exportToCSV(const std::string& filename) const
    {
        //creates an outputFile stream called outputFile and associates it with a file passed in through the filename parameter
        std::ofstream outputFile(filename);

        //error handling; prints if there is an issue with opening the outputFile
        if(!outputFile.is_open())
        {
            std::cerr << "Error, failed to open file" << filename << std::endl;
            //exits function, returns
            return;
        }
        //print header at the top of the CSV
        outputFile << "key, filepath, frequency" << std::endl;
        //calls inorderTraversal, a private function of the AVltree
        inOrderTraversal(root, outputFile);
        //close output file
        outputFile.close();
    }

    /*
    *public AvlTree function to build AvlTree from a CSV file
    *const std::string& filename: the name the file which the AvlTree will be written to
    */
    void AVLfromCSV(const std::string& filename) 
    {
        //creates the inputFile from filename, opens it
        std::ifstream inputFile(filename);
        //error handling; prints if there is an issue with opening the inputFile
        if(!inputFile.is_open())
        {
            std::cerr << "Error, failed to open file" << filename << std::endl;
            return;
        }

        //initalized string variable called header
        std::string header;
        //grabs and stores the header at the top of the csv file
        std::getline(inputFile, header);

        //while not the end of the file
        while(!inputFile.eof())
        {
            //grabs lines in the csv
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
                for (long unsigned int i = 0; i < tokens.size() - 2; i += 2)
                {
                    //key will be the 1st thing in the vector, stays the same for the whole line
                    Comparable key = tokens[0];
                    //doc is stored next
                    Value doc = tokens[i+1];
                    //freq is stored after doc(filepath)
                    size_t freq = std::stoi(tokens[i+2]);
                    //call insert with these variables. calling private insert to cut down on function calls
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
     * const Comparable& x: the key of a node (a word); the item to insert.
     * const Value& document: the filepath to a given article
     * const size_t& freq: the frequency associated with a given article
     * AvlNode *&t: the node that roots the subtree
     */
    void insert(const Comparable& x, const Value& document, const size_t& freq, AvlNode *&t)
    {
        //if its not found, the word does NOT already exist inside the map, so insert it
        if (t == nullptr)
        {
            //call the node constructor, give it its key, document and freq into the map
            t = new AvlNode({x, document, freq});
            //increment total
            total++;
            // a single node is always balanced
            return; 
        }
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
            //the word already exists in the AvlTree; so, update the node's data by inserting the document and the freq into the node's map
            t->data[document] += freq;

        } 

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }

    /**
     * Internal method to check if a given key (x) is found in a subtree rooted at t.
     * const Comparable& x: the key of a node (a word); the term we are searching for
     * AvlNode *&t: the node that roots the subtree
     */
    bool contains(const Comparable &x, AvlNode *t) const
    {
        //if root is null, the tree is empty; return
        if (t == nullptr)
            return false;
        //if the key is encountered, the element is found; return true
        if (x == t->key)
            return true; 
        //recursive call; if x is less than the key of a given node, search the tree again and pass in the node's left child
        else if (x < t->key)
            return contains(x, t->left);
        //recursive call; if x is less than the key of a given node, search the tree again and pass in the node's right child
        else
            return contains(x, t->right);
    }

    /**
     * Internal method to return the map associated with a given node if it exists in the Avltree
     * const Comparable& x: the key of a node (a word); the term we are searching for
     * AvlNode *&t: the node that roots the subtree
     */
    std::map<Value, size_t> find (const Comparable &x, AvlNode *t) const
    {
        //if root is null, return an empty map
        if (t == nullptr)
            return std::map<Value, size_t>();
        //if the word is found in the map, return its data
        if (x == t->key)
            return t->data; 
        //recursive call of find, passing in a given node's left child
        else if (x < t->key)
            return find(x, t->left);
        //recursive call of find, passing in a given node's right child
        else
            return find(x, t->right);
    }

    /*
    *interal method to sort a node's data from highest frequency to smallest frequency
    * const Comparable x: the key of a node (a word); the node whose data the function is working with
    * AvlNode *&t: the node that roots the subtree
    */
    std::vector<std::pair<Value, size_t>> organize(const Comparable x, AvlNode *t) const
    {
        //get the node's data using the find function
        std::map<Value, size_t> OGdata = find(x, t); 
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
    *internal function to return the first 15 key/value pairs in a node's data
    * const Comparable x: the key of a node (a word); the node whose data the function is working with
    * AvlNode *&t: the node that roots the subtree
    */
    std::vector<std::pair<Value, size_t>> first15(const Comparable& x, AvlNode *t) const
    {
       //retrieve the node's organized data from the organize() function
        std::vector<std::pair<Value, size_t>> nodeData = organize(x, t);
        //intialize an empty vector called results, which will be returned at the end of the function
        std::vector<std::pair<Value, size_t>> results;
        //initalize a variable called count to keep track of the amount of elements placed into the results map
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
    *internal function for in order tree traversal
    * AvlNode *&t: the node that roots the subtree
    * std::ofstream& outputFile: the file to which the function prints
    */
    void inOrderTraversal(AvlNode *t, std::ofstream& outputFile) const
    {
        //if null, return
        if (t == nullptr)
        {
            return;
        }
        //recursive call with a given node's left child; traverse and print left subtree
        inOrderTraversal(t->left, outputFile);

        //printing the node's key
        outputFile << t->key;
        //iterates through the node's data map and prints the values seperated by commas
        for (const auto& pair : t->data)
        {
            outputFile << "," << pair.first << "," << pair.second;
        }
        //ends the line
        outputFile << std::endl;
        //recursive call with a given node's right child; traverse and print right subtree
        inOrderTraversal(t->right, outputFile);
    }

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