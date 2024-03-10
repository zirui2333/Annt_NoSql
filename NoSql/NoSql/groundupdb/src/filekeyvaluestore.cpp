//
//  filekeyvaluestore.cpp
//  NoSql
//
//  Created by Zirui Zheng  on 3/9/24.
//
#include "extdatabase.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace groundupdbext{


namespace fs = std::filesystem;

class FileKeyValueStore::Impl{
public:
    Impl(std::string fullpath);
    std::string m_fullpath;
    
private:
    
};


FileKeyValueStore::Impl::Impl(std::string fullpath)
    : m_fullpath(fullpath)
{
    
}


FileKeyValueStore::FileKeyValueStore(std::string fullpath)
    : mImpl(std::make_unique<FileKeyValueStore::Impl>(fullpath))
{
    if(!fs::exists(fullpath)){
        fs::create_directory(fullpath);
    }
}
FileKeyValueStore::~FileKeyValueStore(){
    
}

//Key-value user functions
void FileKeyValueStore::setKeyValue(std::string key, std::string value){
    std::ofstream os;
    os.open(mImpl -> m_fullpath + "/" + key + "_string.kv", std::ios::out | std::ios::trunc);
    
    os << value;
    os.close();
}

std::string FileKeyValueStore::getKeyValue(std::string key){
    std::ifstream is;
    is.open(mImpl -> m_fullpath + "/" + key + "_string.kv", std::ios::in);
    
    std::string value;
    
    is.seekg(0, std::ios::end);
    value.reserve(is.tellg());
    is.seekg(0, std::ios::beg);
    
    value.assign(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());
    return value;
}

//key-value management functions
void FileKeyValueStore::loadKeysInto(std::function<void(std::string key, std::string value)> callback){
//load any files with .kv in their name
    
    for(auto& p : fs::directory_iterator(mImpl -> m_fullpath)){
        if(p.exists() && p.is_regular_file()){
            if(".kv" == p.path().extension()){
                std::string keyWithString = p.path().filename();
                //assusme the file always end with _string.kv
                
                std::string key = keyWithString.substr(0, keyWithString.length() - 10);
                
                std::ifstream is;
                is.open(p.path());
                
                std::string value;
                
                is.seekg(0, std::ios::end);
                value.reserve(is.tellg());
                is.seekg(0, std::ios::beg);
                
                value.assign(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());
                
                callback(key, value);
            }
        }
    }
}

void FileKeyValueStore::clear(){
    if(fs::exists(mImpl -> m_fullpath)){
        fs::remove_all(mImpl->m_fullpath);
    }
}








}

