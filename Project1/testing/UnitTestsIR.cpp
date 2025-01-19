#include "gtest/gtest.h"
#include "IR.h"

class IRTest : public ::testing::Test {
    public:
      void SetUp() {
        IR exampleOne = IR("test_IR_tie.csv")
      }
};

TEST_F(IRTest, CountTests) {
    exampleOne.Run()
}