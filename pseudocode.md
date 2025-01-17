Project Pseudocode for Answers.md

Workflow:
    1. press 1 to create index
    2. pass in directory filepath
    3. iterate through directory, check  if they are .json files
    4. tokenize, lowercase, etc
    5. add to correspending AVL (to personAVL if person, orgAVL if org, all words to wordAVL). if the node doesn't exist, add to tree.
    if the node exists, update the frequency at the given filepath by 1
    6. return time taken to create index
    7. query
    8. enter input, tokenize input, put into vector and pass to query processor
    9. tokenize input, check for words to negate
    10. search for the query in AVL. if query is more than one term, erase word when corresponding map is returned
    11. compare maps to calculate intersections between, order the map from least to greatest by frequency. remove negated words if applicable
    update ranked results
    12. return results map to UI
    13. print results
    14. offer option to read article text, print if desired
    15. menu; options to index, collapse to csv, build from csv, view statistics

Class IndexHandler:
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


Class QueryProcessor:
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


Class DocumentParser:
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



Template Class AvlTree:
        struct Avlnode
        AvlNode root
        size_t total
        static const int ALLOWED_IMBALANCE

    Function insert(x, document, freq, t)
        if t is not found
            create new node, passing x, document, and freq
            increment total
            return
        if x is less than t->key
            recursive call with t->left
        else if t->key is less than x
            recursive call with t->right
        else
            update t's map by inserting with document, freq
        balance tree

    Function find(x, t)
        if t is null
            return empty map
        if x equals t->key
            return t's data
        else if x is less than t->key
            recursive call with t->left
        else
            recursive call with t->right

    Function organize(x, t)
        initalize map OGData with map returned from find function
        create vector of pairs organizedData which is the copied data of OGData
        sort organizedData based on pair.second (the frequency)
        return organizedData

    Function getTotal()
        return count of unique keys

    Function contains(x, t)
        if t is null
            return false
        if t is encountered
            return true
        else if x is less than t->key
            recursive call with t->left
        else
            recursive call with t->right

    Function first15(x, t)
        initalize vector of pairs called nodeData with the map returned from organize
        intialize empty vector of pairs results
        intialize count with 0
        iterate through nodeData
            if not at the end and count is not 15
                add the pair to results
                increment count
        return results

    Function exportToCSV(filename)
        creates outputFile stream outputFile
        if outputFile does not open
            print error message
            return
        print header to outputFile
        calls inOrderTraversal with root, outputFile
        close outputFile
        
    Function AVLfromCSV(filename)
        creates inputFile from filename
        if inputFile does not open
            prints error message
            return
        inialize string header
        getline to store header at top of csv
        while not end of file
            initalize string line
            while function can grab line from inputFile
                initalize vector tokens
                split line into tokens
                push tokens into tokens vector
                iterate through tokens vector
                    variable key set to first entry in tokens
                    variable doc set to tokens at index + 1
                    variable freq set to tokens at index + 2, casts this ch to int
                    calls insert with key, doc, freq and root
        close inputFile

    Function inOrderTraversal(t, outputFile)
        if t is null
            return
        recursive call with t->left
        print t->key to outputFile
        for every pair in t's map (data)
            print comma, print pair.first (filepath), print comma, print pair.second(frequency)
        print endl
        recursive call with t->right

Class UserInterface:
        Documentparser parser
        QueryProcessor queryprocessor
        indexStartTime
        indexEndTime
        queryStartTime
        queryEndTime

    Function index()
        starts time
        initalizes string userPath
        prompts user for directory path
        reads in input
        calls parser's testFileSystem with input
        ends time
        calculates duration
        prints duration to terminal

    Function indexToFile()
        calls exportToCSV on wordAVl using queryprocessor's handler, passing in a csv
        calls exportToCSV on personAVl using queryprocessor's handler, passing in a csv
        calls exportToCSV on organizationdAVl using queryprocessor's handler, passing in a csv

    Function AVLfromFile()
        calls AVLfromCSV on wordAVl using queryprocessor's handler, passing in a csv
        calls AVLfromCSV on personAVl using queryprocessor's handler, passing in a csv
        calls AVLfromCSV on organizationAVl using queryprocessor's handler, passing in a csv

    Function query()
        starts time
        initalizes vector of strings input
        initalizes string line
        prompts user for query
        reads in user's query
        while line is not empty
            split user's query into tokens
            push each token into input
            clear line
        call processQuery and pass in input as parameter
        initalize vector final with vector returned from queryprocessor's getResults
        if final is empty
            print "no results found"
            exit function
        iterate through final
            in each loop, print index, article title, article publication date, article publication, endl
        stop time
        calculate elapsed time
        print elapsed time to terminal
        ask user if they would like to view an article's full text
        initalize char choice
        retrieve user input and store in choice
        if user indicates yes
            initalize int selection as 0
            prompt user to specify which article text they would like to see by inputting the article's corresponding number
            retrieve user input
            call UI's fullArticle function and pass article's filepath


    Function fullArticle(filepath)
        initalizes string fullArticle with the result of parser's fullArticle function, passing parser's fullArticle the filepath passed in as a parameter
        prints fullArticle to terminal

    Function stats()
        prints total amount of articles in index by calling parser's getCount function
        prints total amount of nodes in wordAVL by calling queryprocessor's handler's uniqueWords function

    Function menu()
        while true
            prints menu options
            initalizes int choice as 0
            saves user input in choice variable
            if input is not an int
                print error message
                clears input
                ignore input buffer
                continue
            switch
                calls corresponding function according to the value of choice





