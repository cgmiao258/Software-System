// IRCandidate.cpp created by Ruichen He and Hannah Nelson
// Candidate class for an IR election, holds votes and returns them.
// Keeps track of whether the candidate is still in the race.

#include <iostream>
#include "IRCandidate.h"

IRCandidate::IRCandidate(std::string name) : DataStructure(name) {
    inRace = true;
}

void IRCandidate::AddVotes(std::vector<int> vote) {
    //Add the input vote to the votes vector
    votes.push_back(vote);
    numVotes++;
}

std::string IRCandidate::DisplayVotes() {
    //Go over each vote, and construct the string for the whole vote list
    std::string ending;
    for (auto& vote : votes) {
        for (int id : vote) {
            //std::cout << id  << " ";
            ending += std::to_string(id) + " ";
        }
        //std::cout << std::endl;
        ending += "\n";
    }
    return ending;
}

bool IRCandidate::IsInRace() {
    return inRace;
}

std::vector<std::vector<int>> IRCandidate::GetVotes() {
    inRace = false;
    return votes;
}