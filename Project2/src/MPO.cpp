// MPO.cpp created by Max Bryson, Hannah Nelson
// Multiple Popularity Only election type. Distributes the votes to the candidates.
// Determines which candidates get seats and distributes those to the candidates

#include "MPO.h"
#include "MPOCandidate.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <ctime>
#include <cstdlib> 
#include <random>

MPO::MPO(std::string& filePath) : Election() {
    std::cout << "MPO Election" << std::endl;
    std::cout << "---------------" << std::endl;
    fs.open(filePath);
    audit = AuditSystem(filePath);
    audit.writeLine("MPO Election\n---------------\n");
}

bool comparePointerToCandidate(MPOCandidate* a, MPOCandidate* b){
    return (*a<*b);
}

void MPO::Run() {
    // Extract Candidates
    readIn();
    std::string auditOut; 
    std::vector<MPOCandidate*> mpo_can_vec;
    for(int i=0; i < options.size(); i++){// store options as MPOCandidates for sorting
        mpo_can_vec.push_back(dynamic_cast<MPOCandidate*>(options.at(i)));
        std::cout << options.at(i)->GetName() << ": " << options.at(i)->GetNumVotes() << std::endl;
        auditOut = options.at(i)->GetName() + ": " + std::to_string(options.at(i)->GetNumVotes()) + "\n";
        audit.writeLine(auditOut); // prints while we are already looping
    }


    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(mpo_can_vec.begin(), mpo_can_vec.end(), gen); //shufle positions so there is no position bias
    std::stable_sort(mpo_can_vec.begin(), mpo_can_vec.end(), comparePointerToCandidate); //sort vectors from low to high
    std::reverse(mpo_can_vec.begin(), mpo_can_vec.end()); //make list go from high to low

    std::cout << "Seats Available: " << numSeats << std::endl;
    auditOut = "Seats Available: " + std::to_string(numSeats) + "\n";
    audit.writeLine(auditOut);
    for(int i=0; i < numSeats; i++){
        std::cout << "Winner of seat " << (i+1) << ": " << mpo_can_vec.at(i)->GetName() << std::endl;
        auditOut = "Winner of seat " + std::to_string((i+1)) + ": " + mpo_can_vec.at(i)->GetName() + "\n";
        audit.writeLine(auditOut);
    }

}

void MPO::readIn() {
    // read header
    numSeats = std::stoi(fileUtils.ReadSpecificLine(fs, 1));
    numCandidates = std::stoi(fileUtils.ReadNextLine(fs));

    // extract candidates and parties
    std::vector<std::pair<std::string, std::string>> candidate_pairs = namesParties(fileUtils.ReadNextLine(fs));
    
    // add candidates to candidate pool
    for (int i = 0; i < candidate_pairs.size(); i++) {
        MPOCandidate* new_candidate = new MPOCandidate(candidate_pairs[i].first);
        options.push_back(new_candidate);
    }

    numVotes = std::stoi(fileUtils.ReadSpecificLine(fs, 4));

    // read votes
    for(int i = 0; i < numVotes; i++){ //Goes through every vote
        std::vector<int> vote = fileUtils.GetVote(fs);
        for(int j = 0; j < vote.size(); j++){ //traverses vote
            if(vote.at(j) == 1){
                dynamic_cast<MPOCandidate*>(options.at(j))->AddVote();
            }
        }
    }

    fs.close();// File completely read
}

std::vector<std::pair<std::string, std::string>> MPO::namesParties(std::string input) {
    std::string auditOut; 
    std::vector<std::pair<std::string, std::string>> namesAndParties;
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, ']')) {
        size_t nameStart = token.find_first_not_of("[");
        size_t nameEnd = token.find_last_of(",");
        std::string name;
        if (token.at(nameStart) == ',') {
            name = token.substr(nameStart + 3, nameEnd - nameStart-3);
        } else {
            name = token.substr(nameStart, nameEnd - nameStart);
        }
        std::cout << "Name: " << name << std::endl;
        auditOut = "Name: " + name + "\n";
        audit.writeLine(auditOut);

        std::string party(1, token[nameEnd+2]);
        std::cout << "party: " << party << std::endl;
        auditOut = "party: " + party + "\n";
        audit.writeLine(auditOut);

        namesAndParties.emplace_back(name, party);
    }

    return namesAndParties;
}
