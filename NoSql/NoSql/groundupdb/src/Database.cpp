//
//  Database.cpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#include "Database.hpp"
#include "extdatabase.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using namespace groundupdb;
using namespace groundupdbext;



//Hidden database: impl class

class EmbeddedDatabase::Impl : public IDatabase{
public:
    Impl(std::string& dbname, std::string& fullpath);
    
    ~Impl();
    std::string getDirectory();
    
    
    
    //Key-Value use cases
    void setKeyValue(const std::string& key, const std::string& value);
    std::string getKeyValue(const std::string& key);
    
    // management function
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> load(std::string& dbname);
    void destroy();

private:
    std::string m_name;
    std::string m_fullpath;
};



EmbeddedDatabase::EmbeddedDatabase(std::string& dbname, std::string& fullpath)
:mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbname, fullpath))
{
    
}


EmbeddedDatabase::~EmbeddedDatabase(){
    
}

std::string EmbeddedDatabase::getDirectory(){
    return mImpl->getDirectory();
}


//Key-Value use cases
void EmbeddedDatabase::setKeyValue(const std::string& key, const std::string& value){
    
}

std::string EmbeddedDatabase::getKeyValue(const std::string& key){
    return mImpl->getKeyValue(key);
}

// management function
const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(std::string dbname){
    return EmbeddedDatabase::Impl::createEmpty(dbname);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string& dbname){
    return EmbeddedDatabase::Impl::load(dbname);
}

void EmbeddedDatabase::destroy(){
    mImpl->destroy();
}





EmbeddedDatabase::Impl::Impl(std::string& dbname, std::string& fullpath)
:m_name(dbname), m_fullpath(fullpath)
{
    
}


EmbeddedDatabase::Impl::~Impl(){
    
}
// Embeded database


// Management functions
const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbname){
    std::string basedir(".groundupdb");
    if(!fs::exists(basedir)){
        fs::create_directory(basedir);
    }
    std::string dbfolder(basedir + "/" + dbname);
    if(!fs::exists(dbfolder)){
        fs::create_directory(dbfolder);
    }
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);
}


void EmbeddedDatabase::Impl::destroy(){
    if(fs::exists(m_fullpath)){
        fs::remove_all(m_fullpath);
    }
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::load(std::string& dbname){
    std::string basedir(".groundupdb");
    std::string dbfolder(basedir + "/" + dbname);
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);;
}

//Instance
std::string EmbeddedDatabase::Impl::getDirectory(){
    return m_fullpath;
}


void EmbeddedDatabase::Impl::setKeyValue(const std::string& key, const std::string& value){
    std::ofstream os;
    os.open(m_fullpath + "/" + key + "_string.kv", std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

std::string EmbeddedDatabase::Impl::getKeyValue(const std::string& key){
    std::ifstream is;
    is.open(m_fullpath + "/" + key + "_string.kv", std::ios::in);
    
    std::string value;
    
    is.seekg(0, std::ios::end);
    value.reserve(is.tellg());
    is.seekg(0, std::ios::beg);
    
    value.assign((std::istreambuf_iterator<char> (is)),
                 std::istreambuf_iterator<char> ());
    
    is.close();
    return value;
}



