// FileUtils.h created by Ruichen He
// A class of functions involved in file handling.

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/**
 * @class FileUtils
 * @brief A collection of functions to parse through a file.
 **/
class FileUtils{
 public:
  /**
   * @brief Checks if the file exists.
   * @param fs File name.
   **/
  bool IsFileExists(std::ifstream& fs);

  /**
   * @brief Checks the election type of a file.
   * @param fs File name of a csv representing an election.
   * @return String that specifies the election type.
   **/
  std::string CheckVoteType(std::ifstream& fs); //returns "IR" or "OPL"

  /**
   * @brief Reads a single specified line of a file.
   * @param fs File name.
   * @param line_num Line number of the file to be read.
   * @return String representing the entire line in the file.
   **/
  std::string ReadSpecificLine(std::ifstream& fs, int line_num);

  /**
   * @brief Reads a single line of a file starting where the file left off previously.
   * @param fs File name of a csv representing an election.
   * @return String representing the entire line in the file.
   **/
  std::string ReadNextLine(std::ifstream& fs);

  /**
   * @brief Finds the names and party associations within a file.
   * @param fs File name of a csv representing an election.
   * @param line_num Line number of the file to be read.
   * @return A list of paired items, where a name is associated with a party.
   **/
  std::vector<std::pair<std::string, std::string>> GetNamesAndParties(std::ifstream& fs, int line_num); //finds name and party with no ()s
  
  /**
   * @brief Gets a vote from the file.
   * @param fs File name of a csv representing an election.
   * @return A singular vote.
   **/
  std::vector<int> GetVote(std::ifstream& fs);

 private:
  /**
   * @brief Helper function to find pairs of candidates and their parties.
   * @param input A string to analyze
   * @return A vector of pairs of candidates and their associated party.
   **/ 
  std::vector<std::pair<std::string, std::string>> extractNamesAndParties(std::string input); // helper for getnamesandparties
  
  /**
   * @brief Helper function to tranform votes as strings, to votes as vectors containing integers
   * @param input A singular vote as a string.
   * @param delimiter A character that indicates where to split the string.
   * @return A vector representation of a vote.
   **/
  std::vector<int> splitString(std::string input, char delimiter); 
};

#endif  // FILEUTILS_H