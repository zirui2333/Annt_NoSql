//
//  Database.cpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#include "Database.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

Database::Database(std::string dbname, std::string fullpath)
    :m_name(dbname), m_fullpath(fullpath)
{
    std::cout << m_fullpath <<"  is here " << std::endl;
}

// Management functions
Database Database::createEmpty(std::string dbname){
    std::string basedir(".groundupdb");
    if(!fs::exists(basedir)){
        fs::create_directory(basedir);
    }
    std::string dbfolder(basedir + "/" + dbname);
    if(!fs::exists(dbfolder)){
        fs::create_directory(dbfolder);
    }
    return Database(dbname, dbfolder);
}


void Database::destroy(){
    if(fs::exists(m_fullpath)){
        fs::remove_all(m_fullpath);
    }
}

//Instance
std::string Database::getDirectory(){
    return m_fullpath;
}


void Database::setKeyValue(const std::string& key, const std::string& value){
    std::ofstream os;
    os.open(m_fullpath + "/" + key + "_string.kv", std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

std::string Database::getKeyValue(const std::string& key){
    std::ifstream is;
    is.open(m_fullpath + "/" + key + "_string.kv", std::ios::in);
    
    std::string value;
    
    is.seekg(0, std::ios::end);
    value.reserve(is.tellg());
    is.seekg(0, std::ios::beg);
    
    value.assign((std::istreambuf_iterator<char> (is)),
                 std::istreambuf_iterator<char> ());
    return value;
}



