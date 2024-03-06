//
//  GroundUpDB.cpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#include "GroundUpDB.hpp"


GroundUpDB::GroundUpDB(){
    
}

Database GroundUpDB::createEmptyDB(std::string& dbname){
    return Database::createEmpty(dbname);
}
