#include <gtest/gtest.h>
#include "Game/Bowling/Scoring/PlayerScore.h"

using namespace Game::Bowling::Scoring;

// Test clearing scores resets everything to zero
TEST(PlayerScoreTest, ClearResetsScores) {
    PlayerScore ps;
    ps.updateFrameScore(0, 10);
    ps.setTotalScore(50);
    ps.clear();

    EXPECT_EQ(ps.getTotalScore(), 0);
    EXPECT_EQ(ps.getFrameScore(0), 0);
}

// Test score update for a single frame
TEST(PlayerScoreTest, FrameScoreUpdatesCorrectly) {
    PlayerScore ps;
    ps.updateFrameScore(2, 25);
    EXPECT_EQ(ps.getFrameScore(2), 25);
    EXPECT_EQ(ps.getTotalScore(), 0); // total is separate
}

// Test total score update
TEST(PlayerScoreTest, TotalScoreUpdatesCorrectly) {
    PlayerScore ps;
    ps.setTotalScore(100);
    EXPECT_EQ(ps.getTotalScore(), 100);
}

// Test multiple frames updated independently
TEST(PlayerScoreTest, MultipleFramesUpdateIndependently) {
    PlayerScore ps;
    ps.updateFrameScore(0, 10);
    ps.updateFrameScore(1, 20);
    ps.updateFrameScore(9, 30);

    EXPECT_EQ(ps.getFrameScore(0), 10);
    EXPECT_EQ(ps.getFrameScore(1), 20);
    EXPECT_EQ(ps.getFrameScore(9), 30);
    EXPECT_EQ(ps.getFrameScore(5), 0); // untouched frame
}

// Test bounds safety: getFrameScore should not crash on out-of-bound
TEST(PlayerScoreTest, OutOfBoundsFrameReturnsZero) {
    PlayerScore ps;
    EXPECT_EQ(ps.getFrameScore(100), 0);
    EXPECT_EQ(ps.getFrameScore(-1), 0);
}
