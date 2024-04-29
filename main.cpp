#include <iostream>
#include "porter2_stemmer.h"
#include "DocParser.h"
#include "userinterface.h"
#include "Query.h"
#include "IndexHandler.h"
#include "AVLTree.h"
#include <chrono>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>


using namespace std;

int main()
{

    //test commit
    cout << "Usage:\n"
         << "\tIndex all files in <directory> and store the index in one or several files:\n"
         << "\tsupersearch index <directory>\n\n"
         << "\tLoad the existing index and perform the following query:\n"
         << "\tsupersearch query \"social network PERSON:cramer\"\n\n"
         << "\tStart a simple text-based user interface that lets the user create an index,\n\tsave/load the index and perform multiple queries:\n"
         << "\tsupersearch ui\n\n";

    cout << "supersearch not implemented yet." << endl; 


    // UI search;
    // search.menu();


    return 0;
}