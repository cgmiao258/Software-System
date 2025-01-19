// Created by Max Bryson
// Header file that represents a candidate within an MPO election
#include "DataStructure.h"

class MPOCandidate : public DataStructure{
 public: 
  /**
   * @brief Constructor
   * @param name Name of the candidate.
   */
  MPOCandidate(std::string name);

  /**
   * @brief Add a vote to the candidate
   */
  void AddVote();

  friend bool operator== (const MPOCandidate& c1, const MPOCandidate& c2);
  friend bool operator!= (const MPOCandidate& c1, const MPOCandidate& c2);
  friend bool operator< (const MPOCandidate& c1, const MPOCandidate& c2);
  friend bool operator> (const MPOCandidate& c1, const MPOCandidate& c2);
  friend bool operator<= (const MPOCandidate& c1, const MPOCandidate& c2);
  friend bool operator>= (const MPOCandidate& c1, const MPOCandidate& c2);
};