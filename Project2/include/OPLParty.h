// OPLParty.h created by Chris Miao, Max Bryson
// Header file for parties involved in an OPL election.

#include "DataStructure.h"
#include <map>
#include <string>

/**
 * @class OPLParty
 * @brief OPL party that inheirites from the DataStructure class.
 * The party contains the candidates and their votes.
 **/
class OPLParty : public DataStructure {
 public:
  /**
   * @brief Constructor.
   * @param name The name of the party.
   **/
  OPLParty(std::string name);

  /**
   * @brief Add a candidate to a party.
   * @param member Name of the candidate
   **/
  void AddMember(std::string member);

  /**
   * @brief Add a vote to a candidate within the party.
   * @param name The name of the candidate who receives the vote.
   **/
  void AddVote(std::string name);

  /**
   * @brief Get a list of the candidates within the party and their votes.
   * @return A mapping of each candidate and their vote count.
   **/
  std::map<std::string,int> getMemberList();

 private:
  std::map<std::string, int> memberList; //<name, #of votes>
};