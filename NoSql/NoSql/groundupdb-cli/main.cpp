#include <iostream>
#include "GroundUpDB.hpp"
#include "cxxopts.hpp"

cxxopts::Options options("groundupdb-cli", "CLI for GroundUpDB");

void printUsage(){
    std::cout << "Bad config!" << std::endl;
}

int main(int argc, char* argv[]){
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
    
    if(result.count("c") == 1){
        if(result.count("n") == 0){
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }
        //create database
        std::string dbname (result["n"].as<std::string>());
        Database db(GroundUpDB::createEmptyDB(dbname));
        return 0;
    }
    std::cout << "No command specified" << std::endl;
    printUsage();
    return 1;
}
