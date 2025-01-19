// Election.h created by Ruichen He
// Parent class for types of elections.

#include "Election.h"

#include <iostream>

Election::Election() {
    totalVotes = 0;
}

int Election::getCandidateNum(){
    int candidateNum = std::stoi(fileUtils.ReadSpecificLine(fs, 1));
    std::cout << "Candidate number: " << candidateNum << std::endl;
    return candidateNum;
}

Election::~Election(){

}
