//
//  GroundUpDB.cpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#include "GroundUpDB.hpp"
#include "extdatabase.hpp"

using namespace groundupdb;
using namespace groundupdbext;

groundupdb::GroundUpDB::GroundUpDB(){
    
}

std::unique_ptr<IDatabase> GroundUpDB::createEmptyDB(std::string& dbname){
    return EmbeddedDatabase::createEmpty(dbname);
}

std::unique_ptr<IDatabase> GroundUpDB::loadDB(std::string& dbname){
    return EmbeddedDatabase::load(dbname);
}
