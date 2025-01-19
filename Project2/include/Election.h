// Election.h created by Ruichen He
// Parent class for different type of elections.

#ifndef ELECTION_H
#define ELECTION_H

#include <fstream>
#include <string>

#include "FileUtils.h"
#include "DataStructure.h"
#include "AuditSystem.h"

/**
 * @class Election
 * @brief Base class for future types of elections.
 **/
class Election {
 protected:
  std::ifstream fs;
  FileUtils fileUtils;
  int totalVotes;
  std::vector<DataStructure*> options;
  AuditSystem audit;

  /**
   * @brief Get candidate ID.
   * @return Candidate number.
   **/
  int getCandidateNum();

 public:
  /**
   * @brief Constructor
   **/
  Election();

  /**
   * @brief Decoonstructor
   **/
  ~Election();
};

#endif  // ELECTION_H