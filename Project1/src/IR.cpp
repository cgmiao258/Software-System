// IR.cpp created by Ruichen He
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
    std::vector<std::pair<std::string, std::string>> namesAndParties = fileUtils.GetNamesAndParties(fs, 2);
    initializeCandidate(namesAndParties);
    totalVoteCount = std::stoi(fileUtils.ReadSpecificLine(fs, 3));
    distributeVote();
    int bestCandidate = IR::findMajority();
    int round = 0;

    // Begin counting
    std::string auditOut;
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
    std::cout << "Winner: " << dynamic_cast<IRCandidate*>(options[bestCandidate]) -> GetName()<< std::endl;
    auditOut = "Winner: " + dynamic_cast<IRCandidate*>(options[bestCandidate]) -> GetName() + "\n";
    audit.writeLine(auditOut);
    audit.closeAudit();
}

void IR::initializeCandidate(std::vector<std::pair<std::string, std::string>> namesAndParties) {
    for (auto& np : namesAndParties) {
        IRCandidate* new_candidate = new IRCandidate(np.first);
        options.push_back(new_candidate);
    }
}

void IR::listCandidates() {
    for (auto& option : options) {
        if (dynamic_cast<IRCandidate*>(option)->IsInRace() == false) {
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

void IR::distributeVote() {
    for (int i = 0; i < totalVoteCount; i++) {
        std::vector<int> currentVote = fileUtils.GetVote(fs);
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

int IR::findMajority() {
    int currentCandidateId = 0;
    for (auto& option : options) {
        if (dynamic_cast<IRCandidate*>(option)->IsInRace() == false) {
            currentCandidateId++;
            continue;
        }
        int currentVoteCount = dynamic_cast<IRCandidate*>(option) -> GetNumVotes() ;
        if (currentVoteCount * 2 > totalVoteCount) {
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int result = dis(gen);
    return result;
}