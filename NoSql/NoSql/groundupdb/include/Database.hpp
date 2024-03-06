//
//  Database.hpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#ifndef Database_hpp
#define Database_hpp

#include <string>

class Database{
public:
    Database(std::string dbname, std::string fullpath);
    
    std::string getDirectory();
    static Database createEmpty(std::string dbname);
    
    
    //Key-Value use cases
    void setKeyValue(const std::string& key, const std::string& value);
    std::string getKeyValue(const std::string& key);
    
    // management function
    void destroy();
    
protected:
    std::string m_name;
    std::string m_fullpath;
};

#endif /* Database_hpp */
