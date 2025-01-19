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

  /**
   * @brief Helper function that determines if a ballot is valid if it has at least half of the candidates ranked
   * Reads in a line of ballot and decides if there are enough votes.
   * @param vote A vector of ints containing the votes that are going to be verified.
   * @return A bool representing if the ballot is valid or not, returning true if it is or false if it is not.
  */
  bool validateVote(std::vector<int> vote);


  /**
   * @brief Helper function to get the invalid vote list
   * @return An vector of vector of int, representing invalid votes
   **/
  std::vector<std::vector<int>> GetInvalidVotes();

  std::string WinnerName;

 private:
  int totalVoteCount;
  int candidateCount;
  std::vector<std::vector<int>> invalidVotes;

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
  std::vector<std::vector<int>> distributeVote();

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