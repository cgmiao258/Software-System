#include "gtest/gtest.h"
#include "IR.h"
#include "FileUtils.h"

void printAsciiValues(const std::string& str1, const std::string& str2) {
    size_t maxLength = std::max(str1.size(), str2.size());

    for (size_t i = 0; i < maxLength; ++i) {
        char char1 = i < str1.size() ? str1[i] : ' ';
        char char2 = i < str2.size() ? str2[i] : ' ';

        std::cout << "Character " << i + 1 << ": "
                  << "'" << char1 << "' (ASCII: " << static_cast<int>(char1) << ") vs "
                  << "'" << char2 << "' (ASCII: " << static_cast<int>(char2) << ")\n";
    }
}

//Test Case ID#:  Intake-Valid-File-Name-001
TEST(FileUtilsTest, Intake_Valid_File_Name_001){
    FileUtils fileUtils;
    std::ifstream file1("./testing/test_IR.csv");
    EXPECT_TRUE(fileUtils.IsFileExists(file1));
    if (file1.is_open()) {
        file1.close();
    }
}

//Test Case ID#:  Reject-Invalid-File-Name-002
TEST(FileUtilsTest, Reject_Invalid_File_Name_002){
    FileUtils fileUtils;
    std::ifstream file1("none.csv");
    EXPECT_FALSE(fileUtils.IsFileExists(file1));
    if (file1.is_open()) {
        file1.close();
    } 
}

//Test Case ID#:  open-file-003
TEST(FileUtilsTest, open_file_003){
    FileUtils fileUtils;
    std::ifstream file1("./testing/test_IR.csv");
    EXPECT_TRUE(file1.is_open());
    if (file1.is_open()) {
        file1.close();
    }
}

//Test Case ID#: Identify-IR-Vote-Type-004

TEST(IRTest, Identify_IR_Vote_Type_004){
    FileUtils fileUtils;
    std::ifstream file1("./testing/test_IR.csv");
    std::string votetype = fileUtils.CheckVoteType(file1);
    EXPECT_TRUE(votetype == "IR");

    std::ifstream file2("./testing/test_OPL.csv");
    std::string votetype2 = fileUtils.CheckVoteType(file2);
    EXPECT_FALSE(votetype2 == "IR");
}

//Test Case ID#: Identify-OPL-Vote-Type-005
TEST(OPLTest, Identify_OPL_Vote_Type_005){
    FileUtils fileUtils;
    std::ifstream file1("./testing/test_OPL.csv");
    std::string votetype = fileUtils.CheckVoteType(file1);
    EXPECT_TRUE(votetype == "OPL");

    std::ifstream file2("./testing/test_IR.csv");
    std::string votetype2 = fileUtils.CheckVoteType(file2);
    EXPECT_FALSE(votetype2 == "OPL");
}

//Test Case ID#:  Fair-Coin-Toss-006
TEST(IRTest, Fair_Coin_Toss_006){
    std::string fileName = "./testing/test_IR.csv";
    IR election = IR(fileName);
    int flip_0 = 0;
    int flip_1 = 0;
    for (int i = 0; i < 100000; i++){
        if (election.flipCoin() == 0){
            flip_0++;
        } else {
            flip_1++;
        }
    }
    //std::cout << "Ratio: " << float(flip_0)/float(flip_1) << std::endl;
    EXPECT_TRUE(float(flip_0)/float(flip_1) > 0.99 && float(flip_0)/float(flip_1) < 1.01);
}

//Test Case ID#:  P2_008
TEST(IRTest, Validate_Vote_008){
    std::string fileName = "./testing/test_IR.csv";
    IR election = IR(fileName);
    election.Run();
    std::vector<int> valid{1,2,3,4};
    std::vector<int> invalid{-1, -1, -1, 1};
    EXPECT_TRUE(election.validateVote(valid));
    EXPECT_FALSE(election.validateVote(invalid));
}

//Test Case ID#:  P2_009
TEST(IRTest, P2_009_Remove_Invalid_Ballot_Test){
    std::string fileName = "./testing/test_IR_invalid.csv";
    IR election = IR(fileName);
    election.Run();
    std::vector<std::vector<int>> invVotes = election.GetInvalidVotes();
    std::cout<< "Vote length: " << invVotes.size()<< std::endl;
    EXPECT_TRUE(invVotes.size() == 10);
}



//Test Case ID#:  P2_010
TEST(IRTest, P2_010_Remove_Invalid_Ballot_Test_System){
    std::string fileName = "./testing/test_IR_invalid.csv";
    IR election = IR(fileName);
    election.Run();
    std::cout<< election.WinnerName << std::endl;
    std::string expectedWinner = "Rosen ";
    std::cout<< expectedWinner << std::endl;
    std::string actualWinner = election.WinnerName;
    printAsciiValues(expectedWinner,actualWinner);
    EXPECT_TRUE(actualWinner == expectedWinner);
}

