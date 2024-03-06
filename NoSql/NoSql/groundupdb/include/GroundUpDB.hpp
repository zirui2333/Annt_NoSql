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

class GroundUpDB{
public:
    GroundUpDB();
    
    static Database createEmptyDB(std::string& dbname);
};

#endif /* GroundUpDB_hpp */
