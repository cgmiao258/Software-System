// IR.cpp created by Ruichen He and Hannah Nelson
// Runs an Instant runoff election. Starts by distributing votes,
// checks for a majority. If there is no majority, then the candidate with
// the lowest amount of votes gets taken out of the race and their votes get
// redistributed to the others. This process is repeated until the winner is
// found. If there is a tie, each candidate has an equal chance of winning.

#include "IR.h"
#include <iostream>
#include <random>
#include "IRCandidate.h"
#include "AuditSystem.h"

IR::IR(std::string& filePath) : Election() {
    std::cout << "IR Election" << std::endl;
    std::cout << "---------------" << std::endl;
    fs.open(filePath);
    audit = AuditSystem(filePath);
    audit.writeLine("IR Election\n---------------\n");
}

void IR::Run() {
    std::string auditOut;
    std::vector<std::pair<std::string, std::string>> namesAndParties = fileUtils.GetNamesAndParties(fs, 2);
    initializeCandidate(namesAndParties);
    candidateCount = std::stoi(fileUtils.ReadSpecificLine(fs, 1));
    totalVoteCount = std::stoi(fileUtils.ReadSpecificLine(fs, 3));
    
    invalidVotes = distributeVote();

    auditOut = "Removed Invalid Ballots\n";
    audit.writeLine(auditOut);
    for (const auto& innerVec : invalidVotes) {
        auditOut = "";
        for (int num : innerVec) {
            auditOut = auditOut + std::to_string(num) + " ";
        }
        auditOut = auditOut + "\n";
        audit.writeLine(auditOut);
    }
    int bestCandidate = IR::findMajority();
    int round = 0;

    // Begin counting
    
    while (bestCandidate < 0) {
        round++;
        std::cout << "Round: " << round << std::endl;
        auditOut = "Round: " + std::to_string(round) + "\n";
        audit.writeLine(auditOut);
        listCandidates();
        // Find the candidate with lowest vote
        int lowestCandidate = IR::findLowest();
        
        std::cout << "Lowest: " << dynamic_cast<IRCandidate*>(options[lowestCandidate]) -> GetName()<< std::endl;
        auditOut ="Lowest: " + dynamic_cast<IRCandidate*>(options[lowestCandidate]) -> GetName() + "\n";
        audit.writeLine(auditOut);
        // Set the candidate with lowest vote count out of game
        std::vector<std::vector<int>> newVotes = dynamic_cast<IRCandidate*>(options[lowestCandidate]) -> GetVotes();
        // Check the number of vote the candidate has, if larger than 0, redistribute
        if (newVotes.size() > 0) {
            reallocate(newVotes, lowestCandidate);
        }
        // Recalculate the total vote after redistribution
        updateTotalVoteNum();
        // Find the majority again, check if any candidate has vote number ratio larger than 50%
        bestCandidate = IR::findMajority();


        //std::cout << "Best: " << bestCandidate << std::endl;
        std::cout << "---------------" << std::endl;
        audit.writeLine("---------------\n");
    }
    WinnerName = dynamic_cast<IRCandidate*>(options[bestCandidate]) -> GetName();
    std::cout << "Winner: " << WinnerName << std::endl;
    auditOut = "Winner: " + WinnerName + "\n";
    audit.writeLine(auditOut);
    audit.closeAudit();
}

std::vector<std::vector<int>> IR::GetInvalidVotes(){
    std::vector<std::vector<int>> invalidVotesCopy;
    invalidVotesCopy = invalidVotes;
    return invalidVotesCopy;
}

void IR::initializeCandidate(std::vector<std::pair<std::string, std::string>> namesAndParties) {
    for (auto& np : namesAndParties) {
        //Go over each item, and create candidate accordingly
        IRCandidate* new_candidate = new IRCandidate(np.first);
        options.push_back(new_candidate);
    }
}

void IR::listCandidates() {
    for (auto& option : options) {
        if (dynamic_cast<IRCandidate*>(option)->IsInRace() == false) {
            //Only display the in-race candidates
            continue;
        }
        std::string auditOut;
        std::cout << "Candidate Name: " << dynamic_cast<IRCandidate*>(option) -> GetName() <<  std::endl;
        std::cout << "Candidate Vote Count: " << dynamic_cast<IRCandidate*>(option) -> GetNumVotes() <<  std::endl;
        auditOut = "Candidate Name: " + dynamic_cast<IRCandidate*>(option) -> GetName() + "\n";
        audit.writeLine(auditOut);
        auditOut = "Candidate Vote Count: " + std::to_string(dynamic_cast<IRCandidate*>(option) -> GetNumVotes()) + "\n";
        audit.writeLine(auditOut);

        auditOut = dynamic_cast<IRCandidate*>(option) ->DisplayVotes();
        audit.writeLine(auditOut);
    }
}

bool IR::validateVote(std::vector<int> vote){
    int rankedVoteNum = 0;
    //checks if there is a vote
    for (int i : vote) {
        if (i > -1){
            rankedVoteNum = rankedVoteNum + 1;
        }
    }
    //if the count of votes is greater than at least half of the number of candidates, return true
    if (rankedVoteNum * 2 >= candidateCount) {
        return true;
    }
    std::cout<< "invalid ballot:"; //prints invalid ballot
    for (int i : vote) {
        std::cout<< " " << i;
    }
    std::cout << std::endl;
    return false;
}

std::vector<std::vector<int>> IR::distributeVote() {
    std::vector<std::vector<int>> invalidVotesList;
    for (int i = 0; i < totalVoteCount; i++) {
        std::vector<int> currentVote = fileUtils.GetVote(fs);
        bool isValid = validateVote(currentVote);
        //Validate the votes, if not valid, then push into the inValidVotesList 
        if (isValid == false){
            invalidVotesList.push_back(currentVote);
        } else {
            //If the vote is valid, distribute it to the corresponding candidate
            int currentCandidate = 0;
            for (int vote : currentVote) {
                if (vote == 1) {
                    dynamic_cast<IRCandidate*>(options[currentCandidate])->AddVotes(currentVote);
                    break;
                }
                currentCandidate++;
            }
        }
    }
    return invalidVotesList;
}

int IR::findMajority() {
    int currentCandidateId = 0;
    for (auto& option : options) {
        if (dynamic_cast<IRCandidate*>(option)->IsInRace() == false) {
            currentCandidateId++;
            continue;
        }
        int currentVoteCount = dynamic_cast<IRCandidate*>(option) -> GetNumVotes() ;
        if (currentVoteCount * 2 > totalVoteCount) {
            //If the candidate get more than 50% votes, decalre the winner
            return currentCandidateId;
        }
        currentCandidateId++;
    }
    return -1;
}

int IR::findLowest() {
    int currentCandidateId = 0;
    int lowest = totalVoteCount;
    int lowestCandidate = -1;
    for (auto& option : options) {
        if (dynamic_cast<IRCandidate*>(option)->IsInRace() == true) {
            int currentVoteCount = dynamic_cast<IRCandidate*>(option) -> GetNumVotes() ;
            if (currentVoteCount < lowest) {
                lowest = currentVoteCount;
                lowestCandidate = currentCandidateId;
            } else if (currentVoteCount == lowest) {
                // If there are two candidates with same lowest number, then
                // flip coin to decide who is the lowest candidate
                if (IR::flipCoin() == 0) {
                    lowest = currentVoteCount;
                    lowestCandidate = currentCandidateId;
                }
            }
        }
        currentCandidateId++;
    }
    return lowestCandidate;
}

void IR::updateTotalVoteNum() {
    int newTotalVoteNum = 0;
    for (auto& option : options) {
        //If the candidate is still in race, then update the vote count
        if (dynamic_cast<IRCandidate*>(option)->IsInRace() == true) {
            newTotalVoteNum = newTotalVoteNum + dynamic_cast<IRCandidate*>(option) -> GetNumVotes();
        }
    }
    totalVoteCount = newTotalVoteNum;
}

void IR::reallocate(std::vector<std::vector<int>> newVotes, int preCandidate) {
    for (auto& newVote : newVotes) {
        int preCandidateRank = newVote[preCandidate];
        for (int rank = preCandidateRank + 1; rank < options.size()+1; rank++) {
            //Based on the rank in the vote, if the next candidate is in race, distribute it to them
            int currentCandidate = 0;
            for (int vote : newVote) {
                if (vote == rank){
                    dynamic_cast<IRCandidate*>(options[currentCandidate])->AddVotes(newVote);
                    return;
                }
                currentCandidate++;
            }
        }
    }
}

int IR::flipCoin() {
    //Use the random number generator to generate 0/1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int result = dis(gen);
    return result;
}