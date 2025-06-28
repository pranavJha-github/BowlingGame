#include <gtest/gtest.h>
#include "Game/Bowling/Core/FinalFrame.h"
#include "Game/Bowling/Exceptions/GameOverException.h"

using namespace Game::Bowling::Core;

TEST(TestFinalFrame, AllowsThirdRollIfStrike) {
    FinalFrame frame(10);
    frame.roll(10); // Strike
    frame.roll(10); // Bonus 1
    frame.roll(10); // Bonus 2
    EXPECT_TRUE(frame.isComplete());
    EXPECT_EQ(frame.getRolls().size(), 3);
    EXPECT_EQ(frame.getScore(), 30);
}

TEST(TestFinalFrame, AllowsThirdRollIfSpare) {
    FinalFrame frame(10);
    frame.roll(5);
    frame.roll(5); // Spare
    frame.roll(10); // Bonus roll
    EXPECT_TRUE(frame.isComplete());
    EXPECT_EQ(frame.getRolls().size(), 3);
    EXPECT_EQ(frame.getScore(), 20);
}

TEST(TestFinalFrame, DoesNotAllowThirdRollWithoutSpareOrStrike) {
    FinalFrame frame(10);
    frame.roll(4);
    frame.roll(5); // Open frame
    EXPECT_THROW(frame.roll(3), Game::Bowling::Exceptions::GameOverException);
    EXPECT_TRUE(frame.isComplete());
    EXPECT_EQ(frame.getRolls().size(), 2);
    EXPECT_EQ(frame.getScore(), 9);
}

TEST(TestFinalFrame, HandlesMixedScenarioCorrectly) {
    FinalFrame frame(10);
    frame.roll(10);     // Strike
    frame.roll(7);      // Bonus 1
    frame.roll(2);      // Bonus 2
    EXPECT_EQ(frame.getScore(), 19);
}

TEST(TestFinalFrame, BonusResetWorksAsExpected) {
    FinalFrame frame(10);
    frame.roll(10);     // Strike
    frame.roll(4);      // Bonus 1
    frame.roll(5);      // Bonus 2
    frame.resetBonus(); // Should recalculate correctly
    EXPECT_EQ(frame.getScore(), 19);
}