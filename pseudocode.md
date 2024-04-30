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

    Function parseDoc(filePath)
        read document
        if author or publication exists
            extract and store
        tokenize and process text
        add each word to IndexHandler with calculated frequency

    Function tokenize(text)
        split text into words
        for each word
            clean, stem, and remove stopwords

    Function stemWord(word)
        apply stemming algorithm
        return stemmed word

    Function initializeStopWords()
        load stopwords into set



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



