//
//  extdatabase.hpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/6/24.
//

#ifndef extdatabase_hpp
#define extdatabase_hpp

#include "Database.hpp"
#include <functional>

namespace groundupdbext{

using namespace groundupdb;

//Emphemeral

class MemoryKeyValueStore : public KeyValueStore{
public:
    MemoryKeyValueStore();
    MemoryKeyValueStore(std::unique_ptr<KeyValueStore>& toCache);
    ~MemoryKeyValueStore();
    
    //Key-value user functions
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);
    
    //key-value management functions
    void loadKeysInto(std::function<void(std::string key, std::string value)> callback);
    
    void clear();
    
private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};


class FileKeyValueStore : public KeyValueStore{
public:
    FileKeyValueStore(std::string fullpath);
    ~FileKeyValueStore();
    
    //Key-value user functions
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);
    
    //key-value management functions
    void loadKeysInto(std::function<void(std::string key, std::string value)> callback);
    
    void clear();
    
private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};



class EmbeddedDatabase : public IDatabase{
public:
    EmbeddedDatabase(std::string& dbname, std::string& fullpath);
    EmbeddedDatabase(std::string dbname, std::string fullpath, std::unique_ptr<KeyValueStore>& kvStore);
    ~EmbeddedDatabase();
    
    std::string getDirectory();
    
    
    
    //Key-Value use cases
    void setKeyValue(const std::string& key, const std::string& value);
    std::string getKeyValue(const std::string& key);
    
    // management function
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore);
    static const std::unique_ptr<IDatabase> load(std::string& dbname);
    void destroy();
    
    class Impl;
    
private:
    
    std::unique_ptr<Impl> mImpl;
};

}
#endif /* extdatabase_hpp */
