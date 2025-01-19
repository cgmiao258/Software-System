// DataStructure.h created by Ruichen He, Hannah Nelson
// Parent class for objects involved with an election.

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>

/**
 * @class DataStructure
 * @brief Base class for candidates and parrties involved with elections.
 **/
class DataStructure {
 protected:
  std::string name;
  int numVotes;

 public:
  /**
   * @brief Constructor
   * @param name String that is the label for the object.
   **/
  DataStructure(std::string name);

  /**
   * @brief Gets the number of votes this object contains.
   * @return The number of votes the object contains.
   **/
  int GetNumVotes();

  /**
   * @brief Gets the name of the object.
   * @return The name of the object.
   **/
  std::string GetName();

  /**
   * @brief Virtual destructor.
   **/
  virtual ~DataStructure() = default; 
  // Important virtual function, to make DataStructure class a polymorphic base class
  // Later it will support using dynamic_cast to cast from DataStructure to IRCandidate or OPLParty class
};

#endif  // DATASTRUCTURE_H