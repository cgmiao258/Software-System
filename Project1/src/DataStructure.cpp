// DataStructure.cpp created by Ruichen He
// Parent class for types of objects within the elections.

#include "DataStructure.h"

DataStructure::DataStructure(std::string name) : name(name), numVotes(0){

}

int DataStructure::GetNumVotes(){
    return numVotes;
}

std::string DataStructure::GetName(){
    return name;
}