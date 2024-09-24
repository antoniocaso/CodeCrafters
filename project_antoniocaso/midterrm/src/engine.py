from OurSortedList import SortedList
from OurSortedMap import SortedMap
from Trie import Trie
from TdP_collections.hash_table.unsorted_table_map import UnsortedTableMap
from TdP_collections.priority_queue.heap_priority_queue import HeapPriorityQueue
import os
ISDIR=True
ISPAGE=False


class WebSite:
    class Element:
        def __init__(self, isDirectory, name, content, site):
            """
            Is the constructor of the class Element.

            Arguments:
                isDirectory: boolean
                name: String, is the URL of the Element
                content: either list of Elements or String of words
                site: webSite object, is the webSite which contains the Elements
            """
            self._isDirectory = isDirectory
            self._name = name
            self._site = site
            if isDirectory:
                self._content = []
            else:
                self._content = content

        def __lt__(self, otherElem):
            """
            Magic method: when called on an Element, allows to tell if it is lesser than the one given as an input parameter

            Arguments:
                otherElem: Element

            Returns:
                either True of False
            """
            if not isinstance(otherElem, self.__class__):
                raise TypeError("otherElem is not an element")
            if self._name.swapcase() < otherElem._name.swapcase():
                return True
            else:
                return False

        def __le__(self, otherElem):
            """
            Magic method: when called on an Element, allows to tell if it is equal or lesser than the one given as an input parameter

            Arguments:
                otherElem: Element

            Returns:
                either True of False
            """
            if not isinstance(otherElem, self.__class__):
                raise TypeError("otherElem is not an element")
            if self._name.swapcase() <= otherElem._name.swapcase():
                return True
            else:
                return False

        def __eq__(self, otherElem):
            """
            Magic method: when called on an Element, allows to tell if it is equal to the one given as an input parameter

            Arguments:
                otherElem: Element

            Returns:
                either True of False
            """
            if not isinstance(otherElem, self.__class__):
                raise TypeError("otherElem is not an element")
            if self._name == otherElem._name and self._isDirectory == otherElem._isDirectory:
                return True
            else:
                return False

        def __ne__(self, otherElem):
            """
            Magic method: when called on an Element, allows to tell if it is not equal to the one given as an input parameter

            Arguments:
                otherElem: Element

            Returns:
                either True of False
            """
            if not isinstance(otherElem, self.__class__):
                raise TypeError("otherElem is not an element")
            if self._name != otherElem._name or self._isDirectory != otherElem._isDirectory:
                return True
            else:
                return False

        def __gt__(self, otherElem):
            """
            Magic method: when called on an Element, allows to tell if it is greater than the one given as an input parameter

            Arguments:
                otherElem: Element

            Returns:
                either True of False
            """
            if not isinstance(otherElem, self.__class__):
                raise TypeError("otherElem is not an element")
            if self._name.swapcase() > otherElem._name.swapcase():
                return True
            else:
                return False

        def __ge__(self, otherElem):
            """
            Magic method: when called on an Element, allows to tell if it is equal or greater than the one given as an input parameter

            Arguments:
                otherElem: Element

            Returns:
                either True of False
            """
            if not isinstance(otherElem, self.__class__):
                raise TypeError("otherElem is not an element")
            if self._name.swapcase() >= otherElem._name.swapcase():
                return True
            else:
                return False

        def __str__(self):
            """
            Magic method: allows to return the name of the element

            Returns:
                the name property 
            """
            return self._name 
            
        def _returnParent(self):
            return self._siteURL

    """WebSite Methods"""
    def __init__(self, host):
        """
        Is the constructor of the class Website. It initializes the root as a new empty DIR Element.

        Arguments:
            host: String, is the host of the website
        """
        self._host = host
        self._root = self.Element(ISDIR, "" , None, self)
        

    def __isDir(self, elem):
        """
        Returns true if the Element is a directory, otherwise false

        Arguments:
            elem: Element

        Returns:
            boolean
        """
        return elem._isDirectory
        

    def __isPage(self, elem):
        """
        Returns true if the Element is a page, otherwise false

        Arguments:
            elem: Element

        Returns:
            boolean
        """
        return not elem._isDirectory


    def hasDir(self, ndir, cdir):
        """
        Allows to check if a CDIR directory contains another directory NDIR. If NDIR is not present an exception is thrown,
        otherwise the Element is returned.

        Arguments:  
            ndir: String
            cdir: Element
        
        Returns:
            the Element, that is the ndir directory, if found
        """    
        if not isinstance(cdir, self.Element):
            raise TypeError("cdir " + cdir._name + " is not an element")
        if not self.__isDir(cdir):
            raise Exception("cdir " + cdir._name + "is not a directory")
        
        directoryToCheck = cdir._content
        index = SortedList.search(directoryToCheck, WebSite.Element(ISDIR, ndir, None, self))
        if (index) == -1:
            raise Exception("ndir " + ndir + " is not present in cdir " + cdir._name)
        else:
            return directoryToCheck[index]

        
    def newDir(self, ndir, cdir):
        """
        Creates a new NDIR directory inside a CDIR directory.

        Arguments:
            ndir: String
            cdir: Element

        Returns:
            the result of the insert method on the list representing the directory
        """
        if not isinstance(cdir, self.Element):
            raise TypeError("cdir is not an element")
        if not self.__isDir(cdir):
            raise Exception("cdir is not a directory")

        directoryToCheck = cdir._content        
        return SortedList.insert(directoryToCheck, WebSite.Element(ISDIR, ndir, None, self))
       

    def hasPage(self, npag, cdir):
        """
        Allows to check if a CDIR directory contains a page NPAG. If NPAG is not present an exception is thrown,
        otherwise the Element is returned.

        Arguments:  
            ndir: String
            cdir: Element
        
        Returns:
            the Element, that is the npag page, if found
        """     
        if not isinstance(cdir, self.Element):
            raise TypeError("cdir " + cdir._name + " is not an element")
        if not self.__isDir(cdir):
            raise Exception("cdir " + cdir._name + "is not a directory")

        directoryToCheck = cdir._content
        index = SortedList.search(directoryToCheck, WebSite.Element(ISPAGE, npag, None, self))

        if (index) == -1:
            raise Exception("npag " + npag + " is not present in cdir " + cdir._name)
        else:
            return directoryToCheck[index]
        
        
    def newPage(self, npag, cdir):
        """
        Creates a new NPAG page inside a CDIR directory.

        Arguments:
            ndir: String
            cdir: Element

        Returns:
            the result of the insert method on the list representing the directory
        """
        
        if not isinstance(cdir, self.Element):
            raise TypeError("cdir is not an element")
        if not self.__isDir(cdir):
            raise Exception("cdir is not a directory")

        directoryToCheck = cdir._content
        return SortedList.insert(directoryToCheck, WebSite.Element(ISPAGE, npag, None, self))
        
        

    def getHomePage(self):
        """
        Returns the homePage of the website
        """
        return self.hasPage("index.html",self._root)
            

    def _viewInside(self, dir, c, siteString):
        """Returns the contents of all directories """
        """
        Adding c, allows to append all the names of dir's contents to the siteString.

        Arguments:
            dir: list of Elements
            c: String, is the --- to be added
            siteString: String

        Returns:
            String
        
        """
        for i in dir:
            siteString += (c)
            siteString +=(" " + i._name + "\n")
            if self.__isDir(i):
                siteString = self._viewInside(i._content, c + "---",siteString)

        return siteString
        
            
    def getSiteString(self):
        """
        Allows to create a String detailing the whole WebSite hierarchy.

        Returns:
            String
        """
        siteString = ""
        root = self._root._content
        siteString += (self._host + "\n")
        siteString = self._viewInside(root, "---", siteString)
        return siteString
    
        
    def insertPage(self, url, content):
        """
        Allows to insert a new page inside the website.

        Arguments:
            url: String
            content: String, is the contents of the page

        Returns:
            Element
        """
        path = url.split("/")
        nameFile = path.pop(len(path)-1)
        if path.pop(0) != self._host:
            raise Exception("The page is from a different website")
        else:
            cdir = self._root
            for i in path :
                cdir=self.newDir(i,cdir)
            page = self.newPage(nameFile,cdir)  
            page._content = content 


        return page


    def getSiteFromPage(page):
        """
        Allows to retrieve the WebSite to which the page belongs.

        Arguments:
            page: Element

        Returns:
            Website
        """
        return page._site
        
class InvertedIndex:
    """
    Represents the inverted index used to store pages containing a certain word used as a key.
    """

    def __init__(self):
        """
        Is the contructor of the InvertedIndex class.
        """
        self.trie = Trie()


    def addWord(self, keyword):
        """
        Allows to add a word to the inverted index. This is translated to an insertions inside a Trie.

        Arguments:
            keyword: String
        """
        self.trie.insert(keyword)
        pass


    def addPage(self, page, wordList):
        """
        Allows to add a page to the Inverted Index. 

        Arguments:
            page: Element
            wordList: list of words
        """

        #Iterate the page searching for the words in wordlist
        #A sorted map is used to prepare data before the insertion in the heap: this allows to avoid heap maintenance operations since
        #the words are already sorted by priority 
        map = []
        for i in wordList:
            value = SortedMap.search(map,i)
            if value == False: #If the word is already present the only operations to be done is the update of number of occurrences
                SortedMap.insert(map,[i,1])
                self.addWord(i)
            else:
                value[1]+=1 

        #At this point, we can migrate data from the map to the heap. Key is the word of the trie, whereas value
        #is the number of its occurrences inside the page.
        for i in map:
            #Check whether the heap, for that word in the Trie, is already instantiated
            if self.trie.search(i[0]).pageList == None:                  
                self.trie.search(i[0]).pageList = HeapPriorityQueue()                
            #For each word in the map we add the page (and the number of occurrences therein) to the word's pageList
            self.trie.search(i[0]).pageList.add(-i[1], page)          
          

    def getList(self, keyword):
        """
        Allows to retrieve the list of pages containing a certain word.

        Arguments:
            keyword: String
        
        Returns:
            HeapPriorityQueue or throws Exception is heap is empty
        """

        a = self.trie.search(keyword).pageList
        if a == None or a.is_empty():
            raise Exception("The keyword does not have a list of pages")
        else:    
            return a




class SearchEngine:
    """
    Represents a SearchEngine and allows to store websites, entries (both pages and directories) and keeps an inverted index to allow for 
    word searches.
    """

    def __init__(self, namedir):
        """
        Constructor for the SearchEngine class. Entries contains the names of all the elements to be added in the engine. StorageWebsite 
        will be a map containing all the websites for an easy retrieval. Index will be the inverted index.

        Arguments:
            namedir: String, is the directory used to populate the inverted index and generate the websites.
        """

        self._entries = os.listdir("./"+namedir)
        self._storageWebsite = UnsortedTableMap()           
        self.index = InvertedIndex()

        #Open the files containing the words and split the content so to have both the host and the page content.
        for i in self._entries:
            file = open("./"+namedir+"/"+i, mode="r")            
            path = file.readline().strip()
            fileContent = ""
            for line in file.readlines():
                fileContent += line
            pathList = path.split("/")
            host = pathList[0]
            try:
                #First, look to see if the website has already been added
                website = self._storageWebsite.__getitem__(host)          
            except:
                #If not, then create the website and add it to the storage. 
                website = WebSite(host)
                self._storageWebsite.__setitem__(host,website)                                             
            page = website.insertPage(path, fileContent) #Regardless if the website was already added or not, the page is added to the website
                                                         #along with its content.

            wordList = fileContent.split(" ")  
            self.index.addPage(page, wordList) #Page is also added to the inverted index.
            file.close() #File is closed.



    def search(self, keyword, k):
        """
        Given the K pages with the greatest number of occurrences for a given word, this method returns a String containing
        all the websites of which these pages are a part of.

        Arguments:
            keyword: String, is the word 
            k: is the number of pages of which the siteString is requested
        
        Returns:
            String, the string containing the websites
        """

        #Pagelist will have the list of page connected to that word
        #We use PageToInsert to allow for a more efficient reinserting of the removed pages (in order to get the k pages, we can
        #only remove them from the word's heap).
        #Check is a LookUpTable used to verify whether a certain host has already been written inside the StringToReturn.
        pageList = self.index.getList(keyword)                  
        PageToReinsert = UnsortedTableMap()                     
        StringToReturn = ""                                     
        Check = UnsortedTableMap()                              
    
        i = 0
        while i < k :                                           
            node = pageList.remove_min()                        
            priority = node[0]
            page = node[1]     #Until we have reached k, we extract the k pages and parse them to obtain both the priority (how many times
                               #the searched word is in that page) and the page itself.                                  
            PageToReinsert.__setitem__(priority, page)  #Then, we momentarily store the page and the priority.           
            try:
                #At this point we check if the host is already in the Table, if its is then it has already been added to the String, otherwise we 
                #need both to add the URL to the String AND to add the host to the Check table.
                Check.__getitem__(WebSite.getSiteFromPage(page)._host)
            except:
                #If not inside the table, we extract the host from the page and -given the host- retrieve che WebSite object from the storage using
                #the host's name as the key (the Object is the value). After having updated the strintToReturn, we then add the host to the Check 
                #table putting 1 as the value and the host name as the key: this is used just to quickly verify, through the host name used as a String,
                #if a certain host is already present or not.
                host = WebSite.getSiteFromPage(page)._host                               
                website = self._storageWebsite.__getitem__(host)
                StringToReturn += (website.getSiteString())         
                Check.__setitem__(WebSite.getSiteFromPage(page)._host,1)                            
            i+=1
        #After having extracted the k pages we need to reinsernt them inside the word's heap, otherwise future searches on the same word will yield 
        # spoiled results (spoiled by the fact that we have REMOVED some pages indefinitely). Whereas a simple array could'be been used without any
        #significant loss in performance, the reinsertion could not have been done inside the loop: if done inside the loop, the would never get to 
        #remove ALL the k pages but rather the same one at every iteration, since the removed one'd be reinserted just before removing the succeding 
        #page.
        for key, value in PageToReinsert.items():
            pageList.add(key, value)
        return StringToReturn[:-1]