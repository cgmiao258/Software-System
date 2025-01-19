// main.cpp created by Ruichen He, Max Bryson
// Main function that controls the flow of counting the votes for an election.


#include "Election.h"
#include "FileUtils.h"
#include "IR.h"
#include "OPL.h"
int main(){
    bool fileNotFound= true;
    std::string fileName;
    FileUtils fileUtils; //Handle the file
    std::ifstream fs;
    while (fileNotFound) {
        std::cout << "Enter Filename: ";
        std::cin >> fileName;
        fs.open(fileName);
        //Check if the file exist or not
        if (fileUtils.IsFileExists(fs)){  
            std::cout << "Vote file found" << std::endl;
            fileNotFound = false;
        } else {
            std::cout << "Vote file not found, please check the filename" << std::endl;
        }
    }
    
    
    

    //Check vote type
    std::string voteType = fileUtils.CheckVoteType(fs);
    if (voteType == "IR"){
        std::cout << "Vote Type: " << voteType << std::endl;
        IR election = IR(fileName);
        election.Run();
        
    } else if (voteType == "OPL"){
        std::cout << "Vote Type: " << voteType << std::endl;
        OPL election = OPL(fileName);
        election.Run();
    } else {
        std::cout << "None supported vote type: " << voteType << std::endl;
        return 0;
    }

    


    //Close the vote file at the end of the application
    fs.close();

    return 0;
}