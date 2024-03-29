The KeyValue NoSQL to store various type of variables and effciently search the stored variable.

**Guideline**

    ("c,create", "Create a DB")
    ("d,destroy", "Destroy a DB")
    ("s,set", "Set a key in a DB")
    ("g,get", "Get a key from a DB")
    ("n,name","Database name (required)", cxxopts::value<std::string>())
    ("k,key","Key to set/get", cxxopts::value<std::string>())
    ("v,value","Value to set", cxxopts::value<std::string>())

    For example: create a database: -c -n "Any name of your database", 
               set a keyValue pair: -s -n "You existed database" -k "key" -v "value"

**Explaination of "extdatabase", "inMemoryKeyValueStore" and "FileKeyValueStore**":

Before getting into details, the store and keyvalueStore classes serve as interfaces. So instead of key value, we might have a document store in the future serving as another sub-category under store interface. From right now, we have KEY-VALUE store mechinism all implemented. 

And in terms of ways of storage in computer: We have in memory and in disk. 1) InMemoryStore is an unordered_map store type, everything is pushed into the map<string, string>, it can be primary storage or a supporting backup storage. 2) FileStore is storing everything into file by <fstream> and <filesystem>.

After we call the Embeddedatabase [key-value database], the function will first load existing datas from disk by FileStore, and load them into MemoryStore and use memorystore as primary search and set. So any getKey will result faster by map and setKey by memoryStore will happen in both memory and save to disk from data loss.



**Credit**:
 
Thank @adamfowleruk for extremely helpful tutorial for creating database from scratch.
 
Shout out @Yan Chernikov C++ contents for preparing me knowledge of mechnisms and features from C++ 17 ~ C++ 20
