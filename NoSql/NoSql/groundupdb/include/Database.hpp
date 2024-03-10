//
//  Database.hpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#ifndef Database_hpp
#define Database_hpp

#include <string>
#include <memory>

namespace groundupdb{

class Store{
public:
    Store() = default;
    virtual ~Store() = default;
};

class KeyValueStore : public Store{
public:
    KeyValueStore() = default;
    virtual ~KeyValueStore() = default;
    
    
    //Key value user functions
    virtual void setKeyValue(std::string key, std::string value) = 0;
    virtual std::string getKeyValue(std::string key) = 0;
    
    
    //key value management functions
    virtual void loadKeysInto(std::function<void(std::string key, std::string value)> callback) = 0;
    
    virtual void clear() = 0;

};



class IDatabase{
public:
    IDatabase() = default;
    IDatabase(std::string dbname, std::string fullpath);
    
    virtual ~IDatabase() = default;
    virtual std::string getDirectory() = 0;
    
    
    
    //Key-Value use cases
    virtual void setKeyValue(const std::string& key, const std::string& value) = 0;
    virtual std::string getKeyValue(const std::string& key) = 0;
    
    // management function
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname, std::unique_ptr<KeyValueStore>& kvStore);
    
    static const std::unique_ptr<IDatabase> load(std::string& dbname);
    virtual void destroy() = 0;
    
    
};

}

#endif /* Database_hpp */
