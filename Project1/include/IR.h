// IR.h created by Ruichen He, Hannah Nelson
// Header file that represents an Instant Runoff election.

#include "Election.h"

/**
 * @class IR
 * @brief Instant Runoff election type that inheirites from the Election class.
 **/
class IR : public Election{
 public:
  /**
   * @brief Constructor
   * @param filePath File name.
   **/
  IR(std::string& filePath);

  /**
   * @brief Control function for conducting an IR election.
   **/
  void Run();

  /**
   * @brief Helper function to simulate flipping a fair coin.
   * @return An int as representing the candidate.
   **/
  int flipCoin();

 private:
  int totalVoteCount;

  /**
   * @brief Helper function to initialize a candidate.
   * @param namesAndParties A vector containing pairs of candidates and their respective parties.
   **/
  void initializeCandidate(std::vector<std::pair<std::string, std::string>> namesAndParties);

  /**
   * @brief Helper Function that lists the current candidate pool.
   **/
  void listCandidates();

  /**
   * @brief Helper function that distributes votes to their correct candidates.
   **/
  void distributeVote();

  /**
   * @brief Helper function that finds the candidate with the majority vote.
   * @return A candidate ID if there is a majority vote, otherwise -1 to show
   * there is no majority
   **/
  int findMajority();

  /**
   * @brief Helper function that finds the candidate with the lowest number of votes.
   * @return An int representing the id of the candidate, other -1 if there is no lowest.
   **/
  int findLowest();

  /**
   * @brief Helper function to reallocate votes to the next candidate in line.
   * @param newVotes A vector of votes to be distributed to other candidates.
   * @param preCandidate Int representing the previous candidate.
   **/
  void reallocate(std::vector<std::vector<int>> newVotes, int preCandidate);

  /**
   * @brief Helper function to update the total vote number.
   **/
  void updateTotalVoteNum();
};