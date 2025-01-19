// OPLParty.h created by Chris Miao, Max Bryson
// Party class for OPL elections. Holds the candidates within the parties and how
// many each candidate has. As well as the total vote count that the party has.

#include "OPLParty.h"

OPLParty::OPLParty(std::string name) : DataStructure(name) {

}

void OPLParty::AddMember(std::string member) {
    memberList.insert({member, 0});
}

void OPLParty::AddVote(std::string name) {
    memberList[name] += 1;
    numVotes++;
}

std::map<std::string,int> OPLParty::getMemberList() {
    return memberList;
}