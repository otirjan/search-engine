#include "DocParser.h"

using namespace rapidjson;
using namespace std;

// default constructor
DocumentParser::DocumentParser() : handler(), count(0) {
    initializeStopWords();
}

vector<string> DocumentParser::tokenize(const string& text) {
    vector<string> words;
    istringstream stream(text);
    string word;
    while (stream >> word) {
        // remove punctuation (does not remove quotation marks)
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        // lowercase the word
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // stem the word
        // word = stemWord(word);
        // only add to the words vector if it is not a stop word
        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            words.push_back(word);
        }
    }
    //         for(int i=0; i<words.size(); i++){
    //     //cout << "token: " << words[i] << endl;
    // }
    return words;
}

// string DocumentParser::stemWord(string& word){   //just takes in one word, returns that word stemmed

//     string stemWord = word;

//     Porter2Stemmer::trim(stemWord);
//     Porter2Stemmer::stem(stemWord);

//     return stemWord;
// }

void DocumentParser::parseDoc(const string& filePath) {
    // go thru and take out stop words, stem words that need it, and exctact info for each document
    // opens a file for reading using an ifstream object
    ifstream ifs(filePath);
    // error handling; if file doesn't open, print error message
    if (!ifs.is_open()) {
        cerr << "Could not open file: " << filePath << endl;
    }

    // wraps an input stream to be used as a JSON input stream
    IStreamWrapper isw(ifs);
    // empty Document object named document to represent a JSON document
    Document document;
    // parses JSON document from isw into the Document object document
    document.ParseStream(isw);

    // increment variable keeping track of how many articles the DocParser is parsing
    count++;

    // extract people
    if (document.HasMember("entities") && document["entities"].HasMember("persons") && document["entities"]["persons"].IsArray()) {
        // create array of ppl from json file, create ref to pplArray (so that we're not making copies)
        rapidjson::Value& pplArray = document["entities"]["persons"];

        for (rapidjson::SizeType i = 0; i < pplArray.Size(); i++) {  // for loop that goes through the array of ppl
            rapidjson::Value& person = pplArray[i];                  // reference to a person

            if (person.HasMember("name") && person["name"].IsString()) {           // looks thru people array for names
                string name = person["name"].GetString();                          // extracts the name
                handler.addPerson(name, filePath,1);  // call the index handler to add each person to the AVl
            }
        }
    } else {
        cerr << "Error: json file doesn't contain an person or it is not a string" << endl;
    }

    // extract orgs
    if (document.HasMember("entities") && document["entities"].HasMember("organizations") && document["entities"]["organizations"].IsArray()) {
        // create array of orgs from json file, create ref to orgArray (so that we're not making copies)
        rapidjson::Value& orgArray = document["entities"]["organizations"];

        for (rapidjson::SizeType i = 0; i < orgArray.Size(); i++) {  // for loop that goes through the array of ppl
            rapidjson::Value& org = orgArray[i];                     // reference to a person

            if (org.HasMember("name") && org["name"].IsString()) {                              // looks thru people array for names
                string organization = org["name"].GetString();                                  // extracts the name
                handler.addOrg(organization, filePath, 1);  // call the index handler to add each person to the AVl
            }
        }
    } else {
        cerr << "Error: json file doesn't contain an org or it is not a string" << endl;
    }

    // go thru text, tokenize, add words to the word AVL
    string text = document["text"].GetString();
    auto words = tokenize(text);
    for (auto& word : words) {
        // std::cout << word << std::endl;
        handler.addWord(word, filePath);
    }

}  // end parseDoc

// function which returns the total number of articles processed by the doc parser
int DocumentParser::getCount() {
    return count;
}

/*
 *internal function that extracts an article's title
 *const string& filePath: specifies the path to the article
 */
string DocumentParser::getTitle(const string& filePath) {
    // opens a file for reading using an ifstream object
    ifstream ifs(filePath);
    // error handling; if file doesn't open, print error message
    if (!ifs.is_open()) {
        cerr << "Could not open file: " << filePath << endl;
    }

    // wraps an input stream to be used as a JSON input stream
    IStreamWrapper isw(ifs);
    // empty Document object named document to represent a JSON document
    Document document;
    // parses JSON document from isw into the Document object document
    document.ParseStream(isw);
    // declares a string variable called title
    std::string title;

    // if the document finds title in the JSON document, and if title is a string
    if (document.HasMember("thread") && document["thread"].HasMember("title") && document["thread"]["title"].IsString()) {
        // sets the variable title equal to the string extracted from the document
        title = document["thread"]["title"].GetString();
    } else {
        // error handling; alerts that there is an issue accessing the article title
        cerr << "Error: json file doesn't contain a title or it is not a string" << endl;
    }
    // returns the title variable
    return title;
}

/*
 *internal function that extracts an article's publication date
 *const string& filePath:specifies the path to the article
 */
string DocumentParser::getPublishDate(const string& filePath) {
    // opens a file for reading using an ifstream object
    ifstream ifs(filePath);
    // error handling; if file doesn't open, print error message
    if (!ifs.is_open()) {
        cerr << "Could not open file: " << filePath << endl;
    }

    // wraps an input stream to be used as a JSON input stream
    IStreamWrapper isw(ifs);
    // empty Document object named document to represent a JSON document
    Document document;
    // parses JSON document from isw into the Document object document
    document.ParseStream(isw);
    // declares a string variable called publishDate
    std::string publishDate;
    // declares a string variable called temp
    std::string temp;

    // if the document finds "published" in the JSON document, and if "published" is a string
    if (document.HasMember("thread") && document["thread"].HasMember("published") && document["thread"]["published"].IsString()) {
        // sets the temp variable equal to the string extracted from the document
        temp = document["thread"]["published"].GetString();
    } else {
        // error handling; alerts that there is an issue accessing the article publication field
        cerr << "Error: json file doesn't contain a publication date or it is not a string" << endl;
    }

    // declares a size_t value which is the index of the character 'T' in the string temp
    size_t position = temp.find('T');
    // sets the variable publishDate equal to a trimmed string which contains the year, month and date of publication
    publishDate = temp.substr(0, position);
    // returns the publishDate variable
    return publishDate;
}

/*
 *internal function that extracts an article's publication
 *const string& filePath:specifies the path to the article
 */
string DocumentParser::getPublication(const string& filePath) {
    // opens a file for reading using an ifstream object
    ifstream ifs(filePath);
    // error handling; if file doesn't open, print error message
    if (!ifs.is_open()) {
        cerr << "Could not open file: " << filePath << endl;
    }

    // wraps an input stream to be used as a JSON input stream
    IStreamWrapper isw(ifs);
    // empty Document object named document to represent a JSON document
    Document document;
    // parses JSON document from isw into the Document object document
    document.ParseStream(isw);
    // declares a string variable called publication
    std::string publication;

    // if the document finds "site" in the JSON document, and if "site" is a string
    if (document.HasMember("thread") && document["thread"].HasMember("site") && document["thread"]["site"].IsString()) {
        // sets the publication variable equal to the string extracted from the document
        publication = document["thread"]["site"].GetString();
    } else {
        // error handling; alerts that there is an issue accessing the article site field
        cerr << "Error: json file doesn't contain a publication or it is not a string" << endl;
    }
    // returns the publication variable
    return publication;
}

/*
 *internal function that extracts an article's text
 *const string& filePath:specifies the path to the article
 */
string DocumentParser::fullArticle(const string& filePath) {
    // opens a file for reading using an ifstream object
    ifstream ifs(filePath);
    // error handling; if file doesn't open, print error message
    if (!ifs.is_open()) {
        cerr << "Could not open file: " << filePath << endl;
    }

    // wraps an input stream to be used as a JSON input stream
    IStreamWrapper isw(ifs);
    // empty Document object named document to represent a JSON document
    Document document;
    // parses JSON document from isw into the Document object document
    document.ParseStream(isw);
    // declares a string variable called articleText
    std::string articleText;

    // if the document finds "text" in the JSON document, and if "text" is a string
    if (document.HasMember("text") && document["text"].IsString()) {
        // sets the articleText variable equal to the string extracted from the document
        articleText = document["text"].GetString();
    }
    // returns the articleText variable
    return articleText;
}

// function to calculate frequency, will be called when we pass word,doc,freq to add in the index handler
size_t DocumentParser::calcFrequency(const Document& document, const string& word) {
    size_t frequency = 0;  // initialize frequency variable

    // extract all of the text and tokenize it to read each word
    string contents = document["text"].GetString();
    auto words = tokenize(contents);  // words is the collection of words extracted from the text

    for (const auto& w : words) {  // for loop that goes thru all the text, increases frequency if word appears
        if (w == word) {
            frequency++;
        }
    }
    return frequency;

}  // end of calc frequency

// returns a reference to the index handler object that belongs to DocParser as a private variable
IndexHandler& DocumentParser::getIndexHandler() {
    return handler;
}

void DocumentParser::testFileSystem(const string& path)  // this takes in the folder of data and gives us the filepath for each
{
    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);

    int docCount = 0;

    // loop over all the entries.
    for (const auto& entry : it) {
        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            docCount++;
            if (docCount % 30 == 0) {
                auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string time = std::ctime(&now);

                time.pop_back();

                cout << "parsed: " << docCount << "at " << time << endl;
            }

            parseDoc(entry.path().string());  // call parsedoc and pass the file path
        }
    }
}

// words that will be extracted from the documents we parse
void DocumentParser::initializeStopWords() {
    stopwords = {"a", "able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after",
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
