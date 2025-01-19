//MPO.h created by Max Bryson
//Header file for MPO electino type

#include "Election.h"

/**
 * @class MPO
 * @brief Multiple Popularity Only election type that inheirites from the Election class.
 **/
class MPO : public Election{
 public:
  /**
   * @brief Constructor
   * @param filePath File name.
   **/
  MPO(std::string& filePath);

  /**
   * @brief Control function for conducting a MPO election.
   **/
  void Run();


 private:
  int numCandidates;
  int numSeats;
  int numVotes;

  /**
   * @brief Reads within a file are handled here.
   **/
  void readIn(); //handles all reading in file. no read ins should be done outside of this

  std::vector<std::pair<std::string, std::string>> namesParties(std::string input);

};