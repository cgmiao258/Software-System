// FileUtils.cpp created by Ruichen He
// File handeling operations. Checks the election type, if the file exists,
// reading specific lines, and split strings into votes.

#include "FileUtils.h"

bool FileUtils::IsFileExists(std::ifstream& fs){
    return fs.is_open();
}

std::string FileUtils::CheckVoteType(std::ifstream& fs){
    std::string voteType;
    std::getline(fs, voteType);
    return voteType;
}

std::string FileUtils::ReadSpecificLine(std::ifstream& fs, int line_num){
    // The num of the first line will be 0
    std::string line;
    int current_line = 0;
    fs.seekg(0);
    while(std::getline(fs, line)){
        if (current_line == line_num){
            return line;
        }
        current_line++;
    }
    
    throw std::out_of_range("Line num out of range");
}

std::string FileUtils::ReadNextLine(std::ifstream& fs){
    // The num of the first line will be 0
    std::string line;
    if (std::getline(fs, line)){
        return line;
    }
    throw std::out_of_range("Line num out of range");
}

std::vector<std::pair<std::string, std::string>> FileUtils::GetNamesAndParties(std::ifstream& fs, int line_num){
    std::string line = ReadSpecificLine(fs, line_num);
    std::vector<std::pair<std::string, std::string>> namesAndParties = extractNamesAndParties(line);
    return namesAndParties;
}

std::vector<int> FileUtils::GetVote(std::ifstream& fs){
    std::string currentVote = ReadNextLine(fs);
    std::vector<int> currentVoteInVector =  splitString(currentVote, ',');
    return currentVoteInVector;
}

std::vector<std::pair<std::string, std::string>> FileUtils::extractNamesAndParties(std::string input) {
    std::vector<std::pair<std::string, std::string>> namesAndParties;
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, ',')) {
        size_t nameStart = token.find_first_not_of(" ");
        size_t nameEnd = token.find_last_of(" (");
        std::string name = token.substr(nameStart, nameEnd - nameStart);
        //std::cout << "Name: " << name << std::endl;

        size_t partyStart = token.find('(');
        std::string party(1, token[partyStart + 1]);
        //std::cout << "party: " << party << std::endl;

        namesAndParties.emplace_back(name, party);
    }

    return namesAndParties;
}

std::vector<int> FileUtils::splitString(std::string input, char delimiter) {
    std::vector<int> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    
    while (std::getline(tokenStream, token, delimiter)) {
        if (token == ""){
            tokens.push_back(-1); 
        } else {
            tokens.push_back(std::stoi(token)); 
        }
    }

    if (!input.empty() && input.back() == delimiter) {
        tokens.push_back(-1);
    }
    
    return tokens;
}
