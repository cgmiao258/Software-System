//Created by Max Bryson
//Candidate class for MPO elections
//Candidates hold names and their number of votes
//Comparison operators overloaded for comparison based on number of votes

#include "MPOCandidate.h"


MPOCandidate::MPOCandidate(std::string name) : DataStructure(name) {

}

void MPOCandidate::AddVote(){
    numVotes++;
}

bool operator== (const MPOCandidate& c1, const MPOCandidate& c2){
    return (c1.numVotes == c2.numVotes);
}

bool operator!= (const MPOCandidate& c1, const MPOCandidate& c2){
    return (c1.numVotes != c2.numVotes);
}

bool operator< (const MPOCandidate& c1, const MPOCandidate& c2){
    return (c1.numVotes < c2.numVotes);
}

bool operator> (const MPOCandidate& c1, const MPOCandidate& c2){
    return (c1.numVotes > c2.numVotes);
}

bool operator<= (const MPOCandidate& c1, const MPOCandidate& c2){
    return (c1.numVotes <= c2.numVotes);
}

bool operator>= (const MPOCandidate& c1, const MPOCandidate& c2){
    return (c1.numVotes >= c2.numVotes);
}