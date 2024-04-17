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

        DocumentParser(){
            initializeStopWords();
        }

        vector <string> tokenize (const string& text){
            vector<string> words;
            istringstream stream(text);
            string word;
            while (stream >> word){
                //remove punctuation
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                //lowercase the word
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                //stem the word
                word = stemWord(word); 
                //only add to the words vector if it is not a stop word
                if (!word.empty() && stopwords.find(word) == stopwords.end()) {
                words.push_back(word); 
                }
            }
            return words;
        }


        string stemWord(string& word){   //just takes in one word, returns that word stemmed

            string stemWord = word;

            Porter2Stemmer::trim(stemWord);
            Porter2Stemmer::stem(stemWord);  

            return stemWord; 
        }


        void parseDoc(const string& filePath){
        //go thru and take out stop words, stem words that need it, and exctact info for each document
            
            ifstream ifs(filePath);
            if (!ifs.is_open()) {
            cerr << "Could not open file: " << filePath << endl;
             }

            IStreamWrapper isw(ifs);
            Document document;
            document.ParseStream(isw);

            //extract author
            if (document.HasMember("author") && document["author"].IsString()) {
             string author = document["author"].GetString();
            } else {
            cerr << "Error: json file doesn't contain an author or it is not a string" << endl;
            }

            //extract the publication 
            if (document.HasMember("publication") && document["publication"].IsString()) {
             string publication = document["publication"].GetString();
            } else {
            cerr << "Error: json file doesn't contain a publication or it is not a string" << endl;
            }

               
            //extract people
            if (document.HasMember("persons") && document["persons"].IsArray()) {
             //create array of ppl from json file, create ref to pplArray (so that we're not making copies)
             rapidjson::Value& pplArray = document["persons"];
             
             for(rapidjson::SizeType i=0; i< pplArray.Size(); i++){    //for loop that goes through the array of ppl
                rapidjson::Value& person = pplArray[i];                //reference to a person 

                if (person.HasMember("name") && person["name"].IsString()){    //looks thru people array for names
                    string name = person["name"].GetString();                 //extracts the name 
                    handler.addPerson(name, filePath, calcFrequency(document, name));                //call the index handler to add each person to the AVl 
                }
             }
            } else {
            cerr << "Error: json file doesn't contain an person or it is not a string" << endl;
            }

            //extract orgs
            if (document.HasMember("organization") && document["organization"].IsArray()) {
            //create array of orgs from json file, create ref to orgArray (so that we're not making copies)
             rapidjson::Value& orgArray = document["organizations"];
             
             for(rapidjson::SizeType i=0; i< orgArray.Size(); i++){    //for loop that goes through the array of ppl
                rapidjson::Value& org = orgArray[i];                //reference to a person 

                if (org.HasMember("name") && org["name"].IsString()){    //looks thru people array for names
                    string organization = org["name"].GetString();                 //extracts the name 
                    handler.addOrg(organization, filePath, calcFrequency(document, organization));                //call the index handler to add each person to the AVl 
                }
             }
            } else {
            cerr << "Error: json file doesn't contain an org or it is not a string" << endl;
            }

            //go thru text, tokenize, add words to the word AVL
            string text = document["text"].GetString();
            auto words = tokenize(text);
            for (const auto& word : words){
                handler.addWord(word, filePath, calcFrequency(document, word));     
            }

        }//end parseDoc


        //function to calculate frequency, will be called when we pass word,doc,freq to add in the index handler 
        size_t calcFrequency(const Document& document, const string& word){
            size_t frequency = 0;           //initialize frequency variable 

            //extract all of the text and tokenize it to read each word 
            string contents = document["text"].GetString();
            auto words = tokenize(contents);               //words is the collection of words extracted from the text

            for(const auto& w: words){     //for loop that goes thru all the text, increases frequency if word appears 
                if(w==word){
                    frequency++;
                }
            }
            return frequency;

        }//end of calc frequency


          
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

        void initializeStopWords(){
            stopwords = {"able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after",
        "afterwards", "again", "against", "ago", "ahead", "ain't", "all", "allow", "allows", "almost", "alone",
        "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst",
        "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anyways", "anywhere",
        "apart", "appear", "appreciate", "appropriate", "are", "aren't", "around", "as", "a's", "aside", "ask",
        "asking", "associated", "at", "available", "away", "awfully", "back", "backward", "backwards", "be", "became",
        "because", "become", "becomes", "becoming", "been", "before", "beforehand", "begin", "behind", "being",
        "believe", "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief", "but", "by",
        "came", "can", "cannot", "cant", "can't", "caption", "cause", "causes", "certain", "certainly", "changes",
        "clearly", "c'mon", "co", "co.", "com", "come", "comes", "concerning", "consequently", "consider", "considering",
        "contain", "containing", "contains", "corresponding", "could", "couldn't", "course", "c's", "currently", "dare",
        "daren't", "definitely", "described", "despite", "did", "didn't", "different", "directly", "do", "does",
        "doesn't", "doing", "done", "don't", "down", "downwards", "during", "each", "edu", "eg", "eight", "eighty",
        "either", "else", "elsewhere", "end", "ending", "enough", "entirely", "especially", "et", "etc", "even", "ever",
        "evermore", "every", "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example", "except",
        "fairly", "far", "farther", "few", "fewer", "fifth", "first", "five", "followed", "following", "follows", "for",
        "forever", "former", "formerly", "forth", "forward", "found", "four", "from", "further", "furthermore", "get",
        "gets", "getting", "given", "gives", "go", "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't",
        "half", "happens", "hardly", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "hello", "help",
        "hence", "her", "here", "hereafter", "hereby", "herein", "here's", "hereupon", "hers", "herself", "he's", "hi",
        "him", "himself", "his", "hither", "hopefully", "how", "howbeit", "however", "hundred", "i'd", "ie", "if",
        "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.", "indeed", "indicate", "indicated",
        "indicates", "inner", "inside", "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll",
        "its", "it's", "itself", "i've", "just", "k", "keep", "keeps", "kept", "know", "known", "knows", "last", "lately",
        "later", "latter", "latterly", "least", "less", "lest", "let", "let's", "like", "liked", "likely", "likewise",
        "little", "look", "looking", "looks", "low", "lower", "ltd", "made", "mainly", "make", "makes", "many", "may",
        "maybe", "mayn't", "me", "mean", "meantime", "meanwhile", "merely", "might", "mightn't", "mine", "minus", "miss",
        "more", "moreover", "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my", "myself", "name", "namely",
        "nd", "near", "nearly", "necessary", "need", "needn't", "needs", "neither", "never", "neverf", "neverless",
        "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none", "nonetheless", "noone", "no-one",
        "nor", "normally", "not", "nothing", "notwithstanding", "novel", "now", "nowhere", "obviously", "of", "off",
        "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones", "one's", "only", "onto", "opposite", "or",
        "other", "others", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over",
        "overall", "own", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus", "possible",
        "presumably", "probably", "provided", "provides", "que", "quite", "qv", "rather", "rd", "re", "really",
        "reasonably", "recent", "recently", "regarding", "regardless", "regards", "relatively", "respectively", "right",
        "round", "said", "same", "saw", "say", "saying", "says", "second", "secondly", "see", "seeing", "seem", "seemed",
        "seeming", "seems", "seen", "self", "selves", "sensible", "sent", "serious", "seriously", "seven", "several",
        "shall", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some",
        "somebody", "someday", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon",
        "sorry", "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure", "take", "taken", "taking",
        "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that'll", "thats", "that's", "that've", "the",
        "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "there'd",
        "therefore", "therein", "there'll", "there're", "theres", "there's", "thereupon", "there've", "these", "they",
        "they'd", "they'll", "they're", "they've", "thing", "things", "think", "third", "thirty", "this", "thorough",
        "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "till", "to", "together",
        "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "t's", "twice", "two", "un", "under",
        "underneath", "undoing", "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon",
        "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value", "various", "versus", "very",
        "via", "viz", "vs", "want", "wants", "was", "wasn't", "way", "we", "we'd", "welcome", "well", "we'll", "went",
        "were", "we're", "weren't", "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence",
        "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon", "wherever",
        "whether", "which", "whichever", "while", "whilst", "whither", "who", "who'd", "whoever", "whole", "who'll",
        "whom", "whomever", "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without", "wonder",
        "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll", "your", "you're", "yours", "yourself",
        "yourselves", "you've", "zero"};
        }


};//end of doc parser 

