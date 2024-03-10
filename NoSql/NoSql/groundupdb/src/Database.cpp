//
//  Database.cpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/5/24.
//

#include "Database.hpp"
#include "extdatabase.hpp"

#include <filesystem>


using namespace groundupdb;
using namespace groundupdbext;

namespace fs = std::filesystem;
/*
// 'Hidden' store Impl class
class Store::Impl {
public:
  Impl();
private:
};
Store::Impl::Impl() {
  ;
}
// 'Hidden' key value store Impl class
class KeyValueStore::Impl {
public:
  Impl();
private:
};
KeyValueStore::Impl::Impl() {
  ;
}
*/




//Hidden database: impl class

class EmbeddedDatabase::Impl : public IDatabase{
public:
    Impl(std::string& dbname, std::string& fullpath);
    Impl(std::string dbname, std::string fullpath,
           std::unique_ptr<KeyValueStore>& kvStore);
    ~Impl();
    std::string getDirectory();
    
    
    
    //Key-Value use cases
    void setKeyValue(const std::string& key, const std::string& value);
    std::string getKeyValue(const std::string& key);
    
    // management function
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore);
    static const std::unique_ptr<IDatabase> load(std::string& dbname);
    void destroy();

private:
    std::string m_name;
    std::string m_fullpath;
    std::unique_ptr<KeyValueStore> m_keyValueStore;
};









EmbeddedDatabase::Impl::Impl(std::string& dbname, std::string& fullpath)
:m_name(dbname), m_fullpath(fullpath)
{
    
    
    //Explicitly specify base type so it matches the make_qunique expected class
    std::unique_ptr<KeyValueStore> fileStore = std::make_unique<FileKeyValueStore>(fullpath);
    std::unique_ptr<KeyValueStore> memoryStore = std::make_unique<MemoryKeyValueStore>(fileStore);
//
    m_keyValueStore = std::move(memoryStore);
}

EmbeddedDatabase::Impl::Impl(std::string dbname, std::string fullpath,
     std::unique_ptr<KeyValueStore>& kvStore)
: m_name(dbname), m_fullpath(fullpath), m_keyValueStore(kvStore.release()){
    
}

EmbeddedDatabase::Impl::~Impl(){
    
}
// Embeded database



// Management functions
const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbname){
    std::string basedir(".groundupdb");
    
    fs::create_directory(basedir);
    
    if (!fs::exists(basedir)) {
          fs::create_directory(basedir);
      }
    
    std::string dbfolder(basedir + "/" + dbname);
    
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);
}



const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore){
    std::string basedir(".groundupdb");
    if(!fs::exists(basedir)){
        fs::create_directory(basedir);
    }
    std::string dbfolder(basedir + "/" + dbname);
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder, kvStore);
}


void EmbeddedDatabase::Impl::destroy(){
    m_keyValueStore -> clear();
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
    m_keyValueStore -> setKeyValue(key, value);
}

std::string EmbeddedDatabase::Impl::getKeyValue(const std::string& key){
    return m_keyValueStore -> getKeyValue(key);
}





EmbeddedDatabase::EmbeddedDatabase(std::string dbname, std::string fullpath,
                                   std::unique_ptr<KeyValueStore>& kvStore)
: mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbname, fullpath, kvStore)){
    
}

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



const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore){
    return EmbeddedDatabase::Impl::createEmpty(dbname, kvStore);
}




const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string& dbname){
    return EmbeddedDatabase::Impl::load(dbname);
}

void EmbeddedDatabase::destroy(){
    mImpl->destroy();
}
