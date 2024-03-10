#include <iostream>
#include "GroundUpDB.hpp"
#include "cxxopts.hpp"
#include "Time.hpp"

cxxopts::Options options("groundupdb-cli", "CLI for GroundUpDB");

void printUsage(){
    std::cout << "Bad config!" << std::endl;
}

int rest4(int argc, char* argv[]){
    Time timer;
    options.add_options()
    ("c,create", "Create a DB")
    ("d,destroy", "Destroy a DB")
    ("s,set", "Set a key in a DB")
    ("g,get", "Get a key from a DB")
    ("q,query", "Query the DB (must also specify a query term. E.g. b for bucket)")
    ("n,name","Database name (required)", cxxopts::value<std::string>())
    ("k,key","Key to set/get", cxxopts::value<std::string>())
    ("v,value","Value to set", cxxopts::value<std::string>())
    ("b,bucket","Bucket stored in", cxxopts::value<std::string>())
    ;
    auto result = options.parse(argc, argv);
    
    for(int i = 0; i < argc; ++i){
        std::cout << argv[i] << std::endl;
    }
    
    
    if(result.count("c") == 1){
        if(result.count("n") == 0){
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }
        //create database
        std::string dbname (result["n"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase> db(groundupdb::GroundUpDB::createEmptyDB(dbname));
        std::cout << "I am created \n";
        
        if(result.count("d")){
            db -> destroy();
            std::cout << "I am deleted \n";
        }
        return 0;
    }
    
    if (result.count("s") == 1) {
        if (result.count("n") == 0) {
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }
        if (result.count("k") == 0) {
            std::cout << "You must specify a key to set with -k <name>" << std::endl;
            printUsage();
            return 1;
        }
        if (result.count("v") == 0) {
            std::cout << "You must specify a value to set with -v <value>" << std::endl;
            printUsage();
            return 1;
        }
        // Set key value in database
        std::string dbname(result["n"].as<std::string>());
        std::string k(result["k"].as<std::string>());
        std::string v(result["v"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase> db (groundupdb::GroundUpDB::createEmptyDB(dbname));
        db -> setKeyValue(k, v);
        return 0;
    }
    
    if (result.count("g") == 1) {
        if (result.count("n") == 0) {
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }
        if (result.count("k") == 0) {
            std::cout << "You must specify a key to set with -k <name>" << std::endl;
            printUsage();
            return 1;
        }
        // Get key value from database
        std::string dbname(result["n"].as<std::string>());
        std::string k(result["k"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase> db(groundupdb::GroundUpDB::loadDB(dbname));
        std::cout << db->getKeyValue(k) << std::endl;
        return 0;
    }
    
    if(result.count("d") == 1){
        if(result.count("n") == 0){
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }
        std::string dbname = result["n"].as<std::string>();
        std::unique_ptr<groundupdb::IDatabase> db (groundupdb::GroundUpDB::loadDB(dbname));
        db -> destroy();
        return 0;
    }
    
    std::cout << "No command specified" << std::endl;
    printUsage();
    return 1;
}
