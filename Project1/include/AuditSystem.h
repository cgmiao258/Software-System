// AuditSystem.h created by Hannah Nelson
// Header file for the class that produces a file from the lines given to the writeLine functions

#ifndef AUDIT_SYSTEM_H
#define AUDIT_SYSTEM_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * @class Election
 * @brief Base class for future types of elections.
 **/
class AuditSystem {
 private:
  FILE* fp;

 public:
  AuditSystem();
  /**
   * @brief Constructor
   * @param filePath File name.
   **/
  AuditSystem(std::string& filePath);

  /**
   * @brief Decoonstructor
   **/
  ~AuditSystem();

  /**
   * @brief Write line of test to Audit file.
   * @param addition Text to put into an outfile.
   **/
  void writeLine(std::string addition);

  /**
   * @brief Close audit file.
   **/
  void closeAudit();
};

#endif  // AUDIT_SYSTEM_H