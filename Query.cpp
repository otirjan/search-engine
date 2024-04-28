#include "Query.h"

//set handler for queryprocessor as the handler from index handler 
QueryProcessor::QueryProcessor(IndexHandler& indHandler) : handler(indHandler)
{
   initializeStopWords();  
}

std::vector <std::string> QueryProcessor::tokenize (std::vector<std::string>& text)
{
    std::vector<std::string> words;
   
   for (const auto& word: text)
   {
    if (word.find("PERSON:") == 0 || word.find("ORG:") == 0) { //if the word starts w/ ppl or org, dont tokenize 
             words.push_back(word); // add the whole word without tokenizing
         } else 
         {
            // remove punctuation (does not remove quotation marks)
            std::string processedWord = word;
            processedWord.erase(std::remove_if(processedWord.begin(), processedWord.end(), ::ispunct), processedWord.end());
            // lowercase the word
            std::transform(processedWord.begin(), processedWord.end(), processedWord.begin(), ::tolower);
            // stem the word
            processedWord = stemWord(processedWord);
            // only add to the processed words vector if it is not a stop word
            if (!processedWord.empty() && stopwords.find(processedWord) == stopwords.end()) 
            {
                words.push_back(processedWord);
            }
         }
   }  
        return words;    //return vector of tokenized/stemmed words 
}

string QueryProcessor::stemWord(string& word)
{
            string stemWord = word;

            Porter2Stemmer::trim(stemWord);
            Porter2Stemmer::stem(stemWord);  

            return stemWord; 
}

std::vector<std::string> QueryProcessor::processQuery(std::vector<std::string>& query)
{
    std::vector<std::string> tokens = tokenize(query);     //tokenize the query 

    std::vector<std::string> processedQuery;    //make a vector of the query terms thta have been stemmed
   for(auto& word : query) {
        std::string stemmed = stemWord(word); // stem each word in the query
        processedQuery.push_back(stemmed);    // add the stemmed word to the processed query
    }
    return processedQuery;     //this should just return the query without stop words and stuff 
}


//takes in a vector of words already processed 
void QueryProcessor::searchQuery(const std::vector<std::string>& query)
{

    std::vector<std::string> processedQuery;  //to hold tokenized query

    if(processedQuery.empty())  //after removing stopwords, if theres nothing to search for 
    {     
        throw std::runtime_error(" No key words to search. Try again with another query.");
    }

    std::map<std::string, size_t> firstDocs;    //map with results from the first word in the query 

    if(processedQuery[0].find("PERSON:")==0)   //if it starts with people, search the ppl map for the word (without the PEOPLE:)
    {
        firstDocs = handler.searchPerson(processedQuery[0].substr(7));   //add the results (docs+freq) to firstDocs
    } else if (processedQuery[0].find("ORG:")==0)
    {
        firstDocs = handler.searchOrg(processedQuery[0].substr(13));
    } else                                                              //if its not ppl or org, search the word map 
    {
         firstDocs = handler.searchWord(processedQuery[0]);
    }

    processedQuery.erase(processedQuery.begin());  //remove first term we just looked for 

    rankResults(firstDocs, processedQuery);   //pass the map of first docs to rank results and have it compare w rest of query
}


std::vector<std::string> QueryProcessor::rankResults (std::map<std::string, size_t>& firstDocs,std::vector<std::string>& remainingTerms)
{
    std::vector<std::string> results;    //vector to hold the resulting documents 

    if(remainingTerms.empty())
    {    //if there are no more words in the query, just return the 1st map generated 
        for (const auto& doc: firstDocs ) //this map is already sorted by frequency
        {  
            results.push_back(doc.first);
        }
        return results; 
    }

    std::map<std::string, size_t> nextDocs;    //map with results from the next word in the query 

    if(remainingTerms[0].find("PERSON:")==0)   
    {
        nextDocs = handler.searchPerson(remainingTerms[0].substr(7));
    } else if (remainingTerms[0].find("ORG:")==0)
    {
        nextDocs = handler.searchOrg(remainingTerms[0].substr(13));
    } else 
    {
         nextDocs = handler.searchWord(remainingTerms[0]);
    }

    remainingTerms.erase(remainingTerms.begin());  //like before, erase the word we just searched for 

    std::map<std::string, size_t> combinedFreq;   //map to store the documents + total freq of all seacrhed woeds 
    for (const auto& doc : firstDocs){
        combinedFreq[doc.first] += doc.second;   // add the document and its freq(of word 1) to the mao
    }
    for (const auto& doc : nextDocs){
        combinedFreq[doc.first] += doc.second;   // add the document and its freq(of next word) to the map
    }

    std::vector<std::pair<std::string, size_t>> sortedDocs(combinedFreq.begin(), combinedFreq.end());
    std::sort(sortedDocs.begin(), sortedDocs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // highest frequency on top 
    });

    for (const auto& doc: sortedDocs){
        results.push_back(doc.first);  //push the document names w/ highest added freq to the results 
    }


    return rankResults(combinedFreq, remainingTerms); //recursivley search for the remaining terms 

}

void QueryProcessor::initializeStopWords()
{
            stopwords = {"a","able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after",
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


            
    // //go through the docs returned from first doc, check if there are any matching w docs returned from the next word 
    // for(const auto& firstDoc : firstDocs)
    // {
    //     if (nextDocs.find(firstDoc.first) != nextDocs.end()) //if it finds it before reaching the end 
    //     {  
    //         results.push_back(firstDoc.first);  //add to results if it appears in both 
    //     }
    // }//check for no overlapping


