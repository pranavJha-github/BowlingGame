#include <gtest/gtest.h>
#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Exceptions/InvalidRollException.h"
#include "Game/Bowling/Exceptions/TooManyRollsException.h"
#include <Game/Bowling/Core/FinalFrame.h>

using namespace Game::Bowling::Core;

TEST(FrameTest, InitialFrameState) {
    Frame f(1);
    EXPECT_EQ(f.getScore(), 0);
    EXPECT_FALSE(f.isComplete());
    EXPECT_EQ(f.getBonusType(), BonusType::None);
}

TEST(FrameTest, NormalRollsNoBonus) {
    Frame f(1);
    f.roll(3);
    f.roll(5);
    EXPECT_EQ(f.getScore(), 8);
    EXPECT_TRUE(f.isComplete());
    EXPECT_EQ(f.getBonusType(), BonusType::None);
    EXPECT_TRUE(f.isScoringComplete());
}

TEST(FrameTest, SpareBonusRecognition) {
    Frame f(2);
    f.roll(6);
    f.roll(4);
    EXPECT_EQ(f.getBonusType(), BonusType::Spare);
    EXPECT_FALSE(f.isScoringComplete());
    f.addBonus(7);
    EXPECT_EQ(f.getScore(), 17);
    EXPECT_TRUE(f.isScoringComplete());
}

TEST(FrameTest, StrikeBonusRecognition) {
    Frame f(3);
    f.roll(10);
    EXPECT_EQ(f.getBonusType(), BonusType::Strike);
    EXPECT_TRUE(f.isComplete());
    EXPECT_FALSE(f.isScoringComplete());
    f.addBonus(5);
    f.addBonus(2);
    EXPECT_EQ(f.getScore(), 17);
    EXPECT_TRUE(f.isScoringComplete());
}

TEST(FrameTest, InvalidRollThrows) {
    Frame f(4);
    f.roll(8);
    EXPECT_THROW(f.roll(5), Game::Bowling::Exceptions::InvalidRollException);
}

TEST(FrameTest, RollLimitRespected) {
    Frame f(5);
    f.roll(10);  // Strike ends frame
    EXPECT_TRUE(f.isComplete());
    EXPECT_THROW(f.roll(2), std::runtime_error);
}

TEST(FrameTest, BonusResetWorks) {
    Frame f(6);
    f.roll(10);
    f.addBonus(3);
    f.addBonus(4);
    EXPECT_EQ(f.getScore(), 17);
    f.resetBonus();
    EXPECT_EQ(f.getScore(), 10); // Should only include raw score after reset
}

TEST(FrameTest, GetRollsCorrectness) {
    Frame f(7);
    f.roll(2);
    f.roll(3);
    const auto& rolls = f.getRolls();
    ASSERT_EQ(rolls.size(), 2);
    EXPECT_EQ(rolls[0], 2);
    EXPECT_EQ(rolls[1], 3);
}

// Invalid pin count > 10
TEST(FrameTests, ShouldThrowOnSingleRollGreaterThanTen) {
    Game::Bowling::Core::Frame frame(1);
    EXPECT_THROW(frame.roll(11), Game::Bowling::Exceptions::InvalidRollException);
}

// Invalid combined pins > 10 on second roll
TEST(FrameTests, ShouldThrowIfRollsSumExceedsTen) {
    Game::Bowling::Core::Frame frame(1);
    frame.roll(6);
    EXPECT_THROW(frame.roll(5), Game::Bowling::Exceptions::InvalidRollException);
}
