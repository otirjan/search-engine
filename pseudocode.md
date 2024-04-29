Project Pseudocode for Answers.md

Class IndexHandler
    AvlTree wordAVL, personAVL, organizationAVL

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
        return wordAVL.getTotal()


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
            clean and stem word
            if not a stopword
                add to list

    Function stemWord(word)
        trim and apply stemming algorithm
        return stemmed word

    Function searchQuery(processedQuery)
        for each word in processedQuery
            result = handler.search corresponding type
            integrate results
        rankResults()

    Function rankResults(firstDocs, remainingTerms)
        merge and sort document frequencies
        filter out excluded terms
        recursively integrate remaining terms


Class DocumentParser
    Set stopwords

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



