//
//  extdatabase.hpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/6/24.
//

#ifndef extdatabase_hpp
#define extdatabase_hpp

#include "Database.hpp"

namespace groundupdbext{

using namespace groundupdb;

class EmbeddedDatabase : public IDatabase{
public:
    EmbeddedDatabase(std::string& dbname, std::string& fullpath);
    ~EmbeddedDatabase();
    
    std::string getDirectory();
    
    
    
    //Key-Value use cases
    void setKeyValue(const std::string& key, const std::string& value);
    std::string getKeyValue(const std::string& key);
    
    // management function
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> load(std::string& dbname);
    void destroy();
    
    class Impl;
    
private:
    
    std::unique_ptr<Impl> mImpl;
};

}
#endif /* extdatabase_hpp */
