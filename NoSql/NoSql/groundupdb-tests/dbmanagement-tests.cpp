#include "tests.hpp"
#include "GroundUpDB.hpp"

#include <filesystem>
#include <iostream>
#include <string>


namespace fs = std::filesystem;

int rest3(){
    std::cout << "(Create a new empty database, [createEmptyDB]) \n";
    
    
    // Story:-
    //   [Who]   As a database administrator
    //   [What]  I need to create a new empty database
    //   [Value] So I can later store and retrieve data
    
    std::cout << "Default settings \n";
    
    
    //initialization
    std::string dbname("myemptydb");
    std::unique_ptr<groundupdb::IDatabase> db(groundupdb::GroundUpDB::createEmptyDB(dbname));
    
    // We know we have been successful when:-
    // 1. We have a valid database reference returned
    //   - No test -> The above would have errored
    // 2. The DB has a folder that exists on the file system
    bool openDir = fs::is_directory(fs::status(db -> getDirectory()));
    if(!openDir){
        std::cout << "File is empty \n";
    }else{
        std::cout << "File exists! \n";
        std::cout << fs::absolute(db -> getDirectory());
        //        std::cout << fs::absolute(db.getDirectory());
    }
    
    
    
    // C++17 Ref: https://en.cppreference.com/w/cpp/filesystem/is_directory
    
    // 3. The database folder is empty (no database files yet)
    const auto& p = fs::directory_iterator(db -> getDirectory());
    if(p == end(p)){
        std::cout << "File dictory is empty \n";
    } else{// i.e. no contents as iterator is at the end already
        std::cout << "Dictory has files! \n";
    }
    // C++17 Ref: https://en.cppreference.com/w/cpp/filesystem/directory_iterator
    
    
    
    db -> destroy();
    bool found = fs::exists(fs::status(db -> getDirectory()));
    if(found){
        std::cout << "File deletion failed \n";
    }else{
        std::cout << "File deletion successed \n";
    }
    
    
    
    std::cout<<"db-load [loadDB] \n";
    
    // Story:-
    //   [Who]   As a database user
    //   [What]  I need to create a reference to an existing database
    //   [Value] So I can later store and retrieve data
    
    std::cout <<"Default settings \n";
    dbname = "myemptydb";
    
    std::unique_ptr<groundupdb::IDatabase> d1(groundupdb::GroundUpDB::createEmptyDB(dbname));
    
    std::unique_ptr<groundupdb::IDatabase> d2(groundupdb::GroundUpDB::loadDB(dbname));
    // We know we have been successful when:-
    // 1. We have a valid database reference returned
    //   - No test -> The above would have errored
    // 2. The DB has a folder that exists on the file system
    if(fs::is_directory(fs::status(d2 -> getDirectory()))){
        std::cout << "We have d2 !\n";
        const auto& ptr = fs::directory_iterator(d2 -> getDirectory());
        if(ptr == end(ptr)){
            std::cout << "d2 is emtpy \n";
        }
        d2 -> destroy();
        if(!fs::exists(fs::status(d2 -> getDirectory()))){
            std::cout << "d2 is deleted sussceffully! \n";
        }
        
    }else{
        std::cout <<"We dont have d2 \n";
    }
    
    
    
    
    
       
       
       
       
       
       return 0;
       }
       
       
       
       
