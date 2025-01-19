// OPL.cpp created by Max Bryson, Chris Miao
// Open Party List election type. Distributes the votes to the candidates.
// Determines which parties get seats and distributes those to the candidates.

#include "OPL.h"
#include "OPLParty.h"
#include <iostream>
#include <fstream>
#include <vector>

OPL::OPL(std::string& filePath) : Election(){
    std::cout << "OPL Election"<<std::endl;
    std::cout << "---------------" << std::endl;
    fs.open(filePath);
    audit = AuditSystem(filePath);
    audit.writeLine("OPL Election\n---------------\n");
}

void OPL::Run() {
    readIn();
    findQuota();
    std::cout << "First Allocation of votes"<<std::endl;
    std::string auditOut;  
    auditOut = "First Allocation of votes\n";
    audit.writeLine(auditOut);
    std::vector<int> remainders;
    std::vector<int> seats_given;
    for (int i = 0; i<options.size(); i++){ // award first round of seats
        seats_given.push_back(options.at(i)->GetNumVotes() / quota);
        remainders.push_back(options.at(i)->GetNumVotes() % quota);
        std::cout<<"Party "<<options.at(i)->GetName()<<" gets "<<seats_given.at(i)<<" seats"<<std::endl;
        auditOut = "Party "+options.at(i)->GetName()+" gets "+std::to_string(seats_given.at(i))+" seats\n";
        audit.writeLine(auditOut);
    }

    int seats_remaining = numSeats;
    for (int i = 0; i < seats_given.size(); i++) {  // find remaining seats
        seats_remaining = seats_remaining - seats_given.at(i);
    }

    int largest_remainder_index = 0;
    int largest_remainder = 0;
    for (int i = 0; i < remainders.size(); i++) {  // award seats based on remainders
        if (remainders.at(i) > largest_remainder) {
            largest_remainder = remainders.at(i);
            largest_remainder_index = i;
        } else if (remainders.at(i) == largest_remainder) { //handles ties
            int flip;
            std::vector<int> choices;
            choices.push_back(i);
            choices.push_back(largest_remainder_index);
	        flip=  std::rand() % 2;
            largest_remainder_index = choices.at(flip);
        }
    }

    if (seats_remaining > 0) {
        seats_given.at(largest_remainder_index) = seats_given.at(largest_remainder_index) + seats_remaining;   //award remaining seats
        std::cout<<"Remainder Seats Distributed"<<std::endl;
        auditOut = "Remainder Seats Distributed\n";
        audit.writeLine(auditOut);
    }

    std::vector<std::string> winner_names; // winners list

    // logic is goes through each options(i) which is each party then finds the first winner and compares the next winner by number of votes 
    // making sure that they have the next largest number of votes and then adding them to the winner list 
    for (int i = 0; i < seats_given.size(); i++) {
        if (seats_given.at(i) > 0) {
            std::map<std::string, int> members = dynamic_cast<OPLParty*>(options.at(i))->getMemberList();
            int seats_to_give = seats_given.at(i);

            int last_largest = 0;
            std::string first_winner;
            for (auto i : members) { //finds first winner of that party
                if (i.second > last_largest) {
                    last_largest = i.second;
                    first_winner = i.first;
                }
            }
            winner_names.push_back(first_winner); //first winner
            seats_to_give -= 1;

            int current_largest_vote = 0;
            std::string current_winner;
            while (seats_to_give != 0) { //finds all the winners according to number of seats
                for (auto i : members) {
                    if (i.second > current_largest_vote && i.second < last_largest) {
                        current_largest_vote = i.second;
                        current_winner = i.first;
                    }
                }
                current_largest_vote = 0;
                seats_to_give -= 1;
                winner_names.push_back(current_winner);
                last_largest = current_largest_vote;
            }
        }
    }
    // prints out winners
    std::cout << "Winners are: ";
    for (int i = 0; i < winner_names.size(); i++) {
        std::cout << winner_names.at(i) << " " << std::endl;
        auditOut = winner_names.at(i)+" \n";
        audit.writeLine(auditOut);
    }

}

void OPL::readIn() {
    numCandidates = getCandidateNum();
    std::map<int,int> member_to_party; // first is canidate number, second is party slot
    std::vector<std::pair<std::string, std::string>> candidate_pairs = 
        fileUtils.GetNamesAndParties(fs, 2);
    for(int i = 0; i < candidate_pairs.size(); i++){ //adds all canidates and makes party objects
        bool not_added=true;
        for(int j = 0; j < options.size(); j++){
            if(options.at(j)->GetName() == candidate_pairs.at(i).second && not_added){ //if party matches and not added
                dynamic_cast<OPLParty*>(options.at(j))->AddMember(candidate_pairs.at(i).first); //add member to existing party
                member_to_party.insert({i,j}); // candidate i in party slot j
                not_added=false;
            }
        }
        if(not_added){ //if the party for the member was not been made yet
            OPLParty* new_party = new OPLParty(candidate_pairs.at(i).second); // create new party with candidate name
            new_party->AddMember(candidate_pairs.at(i).first);
            options.push_back(new_party);
            member_to_party.insert({i, options.size() - 1}); //cadidate i in last party slot (new party)
        }
    }

    numSeats = stoi(fileUtils.ReadSpecificLine(fs, 3));
    numVotes = stoi(fileUtils.ReadNextLine(fs));
    
    for(int i = 0; i < numVotes; i++){ //Goes through every vote
        std::vector<int> vote = fileUtils.GetVote(fs);
        for(int j = 0; j < vote.size(); j++){ //traverses vote
            if(vote.at(j) == 1){
                std::string candidate_name = candidate_pairs.at(j).first;
                int party_index = member_to_party[j];
                dynamic_cast<OPLParty*>(options.at(party_index))->AddVote(candidate_name);//ads vote to party and candidate
            }
        }
    }

    fs.close();// NO MORE READING FROM FILE SHOULD BE DONE

}

void OPL::findQuota() {
    quota = numVotes/numSeats;
}