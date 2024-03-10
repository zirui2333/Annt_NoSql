//
//  GroundUpDB.hpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#ifndef GroundUpDB_hpp
#define GroundUpDB_hpp

#include "Database.hpp"
#include <string>

namespace groundupdb{

class GroundUpDB{
public:
    GroundUpDB();
    
    static std::unique_ptr<IDatabase> createEmptyDB(std::string& dbname);
    static std::unique_ptr<IDatabase> createEmptyDB(std::string& dbname, std::unique_ptr<KeyValueStore>& kvStore);
    static std::unique_ptr<IDatabase> loadDB(std::string& dbname);
};

}

#endif /* GroundUpDB_hpp */
