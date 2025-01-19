// IRCandidate.h created by Ruichen He, Hannah Nelson
// Header file that represents a candidate within an IR election

#include "DataStructure.h"
#include <vector>

/**
 * @class IRCandidate
 * @brief IR candidate that inheirites from the DataStructure class.
 * Tracks their name, votes, and whether they are still in the election.
 **/
class IRCandidate : public DataStructure{
 public: 
  /**
   * @brief Constructor
   * @param name Name of the candidate.
   */
  IRCandidate(std::string name);

  /**
   * @brief Add votes to a candidate.
   * @param vote A singular vote.
   */
  void AddVotes(std::vector<int> vote);

  /**
   * @brief Display current votes.
   * @return String of current votes.
   */
  std::string DisplayVotes();

  /**
   * @brief Check if the candidate is in the race.
   * @return Bool that shows if the candidate is in the election.
   */
  bool IsInRace();

  /**
   * @brief Get all of the votes from this candidate and remove from race.
   * @return A vector of votes.
   */
  std::vector<std::vector<int>> GetVotes();

 private:
  std::vector<std::vector<int>> votes;
  bool inRace;
};