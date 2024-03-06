#include <string>
#include <iostream>

#include "GroundUpDB.hpp"
int rest2(){
    std::cout << "Store and retrieve a value, [setKeyValue,getKeyValue] \n";
    
    // Story:-
    //   [Who]   As a database user
    //   [What]  I need to store and retrieve a value with a simple name
    //   [Value] So I can persist data for later use
    
    std::cout << "Basic set and get\n";
    std::string dbname("myemptydb");
    Database db(GroundUpDB::createEmptyDB(dbname));
    
    //We know we have been successful when -
    //1. The retrieved value is the same as the store value
    std::string key("simplestring");
    std::string value("Some highly valuable value");
    db.setKeyValue(key, value);
    if(value == db.getKeyValue(key)){
        std::cout << value << " == " << db.getKeyValue(key) << '\n';
    }else{
        std::cout << value << " is not found! \n";
    }
    
    db.destroy();
    return 0;
}
