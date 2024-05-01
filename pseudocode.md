Project Pseudocode for Answers.md

Class IndexHandler
    AvlTree wordAVL, personAVL, organizationAVL

    Function isValidString(str)
        returns true or false depending on whether or not the string is empty

    Function addWord(word, filePath, freq)
        if isValid(word)
            wordAVL.insert(word, filePath, freq)
            wordAVL.organize(word)

    Function addPerson(word, filePath, freq)
        if isValid(word)
            personAVL.insert(word, filePath, freq)
            personAVL.organize(word)

    Function addOrg(word, filePath, freq)
        if isValid(word)
            organizationAVL.insert(word, filePath, freq)
            organizationAVL.organize(word)

    Function searchWord(word)
        return wordAVL.find(word)

    Function searchPerson(word)
        return personAVL.find(word)

    Function searchOrg(word)
        return organizationAVL.find(word)

    Function uniqueWords()
        return wordAVL.getTotal(), the total number of words in the wordAVL

    Function toLower(word)
        create string result
        iterate through each char in a word
            change the char to lowercase and append to result
        return result

1. Take in a word (already deciphered as person, org, or word) 
2. If its a person, add it to the person AVL
3. If its an org, add it to the org AVL 
4. If its a word, add it to the wordAVL
5. If a user wants to search a person, use find function to look for it in the person AVL and return associated map 
6. If a user wants to search an org, use find function to look for it in the org AVL and return associated map
7. If a user wants to search a word, use find function to look for it in the word AVL and return associated map
8. If prompted, return the total number of words in the avl 


Class QueryProcessor
    IndexHandler handler
    Set stopwords

    Function processQuery(query)
        tokens = tokenize(query)
        for each token
            if token starts with '-'
                add to excludedWords
            else
                stemmed = stemWord(token)
                processedQuery.add(stemmed)
        searchQuery(processedQuery)

    Function tokenize(text)
        for each word in text
            if word starts with "PERSON:"
                extracts substring
                saves substring in variable processedWord
                adds processedWord to words vector
            else if word starts with "ORG:"
                extracts substring
                saves substring in variable processedWord
                adds processedWord to words vector
            else
                removes punctuation
                turns the word to lowercase
                stems the word
                adds word to words vector if the word is not a stop word
        returns words vector

    Function stemWord(word)
        trim and apply stemming algorithm
        return stemmed word

    Function searchQuery(processedQuery)
        if processedQuery is empty
            throw runtime error
        creates a map of string,size_t called firstDocs
        if the first entry in processedQuery starts with "PERSON:"
            search the personAVL
            assign results to firstDocs
        else if the first entry in processedQuery starts with "ORG:"
            search the wordAVL
            assign results to firstDocs
        else
            search for the first entry in processedQuery in the wordAVL
            assigns results to firstDocs
        removes the first entry in processedQuery
        calls rankResults, passing firstDocs and processedQuery
        calls removeNegResults 

    Function rankResults(firstDocs, remainingTerms)
        if remainingTerms is empty
            for every document in the firstDocs map
                adds the document's key (a filepath) to the private query processor vector rankedResults
            returns
        creates a map of string,size_t nextDocs
        if the first entry in remainingterms starts with "PERSON:"
            search the personAVL
            assigns nextDocs to the map that is returned
        else if the first entry in remainingterms starts with "ORG:"
            search the personAVL
            assigns nextDocs to the map that is returned
        else
            assigns nextDocs to the map that is returned when the handler searches wordAVL
        erases the first entry in remainingTerms
        creates a map string,size_t combinedFreq
        for every document in firstDocs
            adds its frequency to the corresponding document's frequency in combindFreq
        for every document in nextDocs
            adds its frequency to the corresponding document's frequency in combindFreq
        copy contents of combinedFreq into vector of pairs called sortedDocs
        sorts sortedDocs by frequency
        recursive call to rankResults until remainingTerms is empty  
    
    Function removeNegResults()
        initalize empty vector newResults
        for every document in rankedResults
            set bool exclude to false
            for every word in the private class vector excludedWords
                extracts the text of the given article
                if an excluded word is found
                    bool exclude is set to true
                    break
            if exclude remains false
                add document to newResults
        replaces contents of private class vector rankedResults with contents of newResults

    Function getResults()
        if private class vector rankedResults is larger than 15
            resize to 15 elements
        return private class vector rankedResults

    Function initializeStopWords()
        load stopwords into set

    Function getHandler()
        returns reference to query processor's handler


Class DocumentParser
    Set stopwords
    int count
    IndexHandler handler

    Function parseDoc(filePath)
        opens file for reading using ifstream object
        if file doesn't open
            print error message
        wraps an input stream to be used as a JSON input stream
        empty Document object named document to represent a JSON document
        parses JSON document from isw into the Document object document
        increment count
        if document has member "entities" and "entities" has member "persons" and "persons" is an array
            iterate over each person in the array
                adds to personAVl with filepath and frequency (calls calcFrequency)
        else
            prints error message
        if document has member "entities" and "entities" has member "organizatiosn" and "organizations" is an array
            iterate over each org in the array
                adds to orgAVL with filepath and frequency (calls calcFrequency)
        else
            prints error message
        creates a string text from the article's text
        tokenizes text
        for every word
            adds to wordAVL with filepath and frequency (calls calcFrequency)

    Function tokenize(text)
        initalize empty vector words
        use istringstream to stream input word by word
        for every word
            remove punctuation
            converts word to lowercase
            stems word
            if word is not a stop word
                push word to words vector
        return vector words

    Function stemWord(word)
        apply stemming algorithm
        return stemmed word

    Function initializeStopWords()
        load stopwords into set
    
    Function caclFrequency(document, word)
        intializes size_t variable frequency to 0
        creates a string variable contents from the document's text
        tokenizes contents
        for every word
            if current word matches the word for which frequency is being counted
                increment frequency
        return frequency

    Function testFileSystem(path)
        traverse through all files and directories within specified path
        for every entry encountered
            if entry is a regular file and if the extension ends is .json
                calls parseDoc

    Function getIndexHandler()
        return reference to doc parser's handler

    Function getTitle(path)
        opens file for reading using an ifstream object
        if file doesn't open
            print error message
        wraps input stream to be used as a JSON input stream
        empty Document object named document to represent a JSON document
        parses JSON document from isw into the Document object document
        declares a string variable title
        if the document has member "thread" and "thread" has member "title" and "title" is a string
            sets title equal to the string extracted from the document
        else
            prints error message
        return title

    Function getPublishDate(path)
        opens file for reading using an ifstream object
        if file doesn't open
            print error message
        wraps input stream to be used as a JSON input stream
        empty Document object named document to represent a JSON document
        parses JSON document from isw into the Document object document
        declares a string variable publishDate
        declares string variable temp
        if the document has member "thread" and "thread" has member "published" and "published" is a string
            sets temp equal to the string extracted from the document
        else
            prints error message
        sets size_t variable equal to the position of the char 'T' in the string temp
        trims temp and sets its result as publishDate
        return publishDate

    Function getPublication(path)
        opens file for reading using an ifstream object
        if file doesn't open
            print error message
        wraps input stream to be used as a JSON input stream
        empty Document object named document to represent a JSON document
        parses JSON document from isw into the Document object document
        declares a string variable publication
        if the document has member "thread" and "thread" has member "site" and "site" is a string
            sets publication equal to the string extracted from the document
        else
            prints error message
        return publication

    Function fullArticle(path)
        opens file for reading using an ifstream object
        if file doesn't open
            print error message
        wraps input stream to be used as a JSON input stream
        empty Document object named document to represent a JSON document
        parses JSON document from isw into the Document object document
        declares a string variable called articleText
        if the document finds "text" in the JSON document, and if "text" is a string
            sets the articleText variable equal to the string extracted from the document
        return articleText

    Function getCount()
        returns count, private class variable keeping track of total articles parsed



Template Class AvlTree
    AvlNode root

    Function insert(key, document, freq)
        if key not present
            create new node
        else
            update node data
        balance tree

    Function find(key)
        locate node with key
        return data map

    Function organize(key)
        retrieve and sort data by frequency

    Function balance()
        apply rotations as necessary to maintain balance

    Function makeEmpty()
        clear the tree recursively

    Function getTotal()
        return count of unique keys

Class UserInterface
    Set stopwords

    Function parseDoc(filePath)
        read document
        if author or publication exists
            extract and store
        tokenize and process text
        add each word to IndexHandler with calculated frequency



