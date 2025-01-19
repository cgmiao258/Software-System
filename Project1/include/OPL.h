// OPL.h created by Max Bryson, Chris Miao
// Header file for an Open Party List election.

#include "Election.h"
#include <string>

/**
 * @class OPL
 * @brief Open Party List election type that inheirites from the Election class.
 **/
class OPL : public Election {
 public:
  /**
   * @brief OPL Constructor
   * @param filePath File name.
   **/
  OPL(std::string& filePath);

  /**
   * @brief Control function for conducting an IR election.
   **/
  void Run();
 private:
  int numCandidates;
  int numSeats;
  int numVotes;
  int quota;

  /**
   * @brief Reads within a file are handled here.
   **/
  void readIn(); //handles all reading in file. no read ins should be done outside of this

  /**
   * @brief Finds quota, which is the number of votes to gain one seat.
   **/
  void findQuota();     
};