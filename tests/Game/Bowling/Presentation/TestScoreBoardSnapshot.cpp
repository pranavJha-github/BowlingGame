#include <gtest/gtest.h>
#include "Game/Bowling/Presentation/ScoreBoardSnapshot.h"

using namespace Game::Bowling::Presentation;

// Test: Default initialization
TEST(TestScoreBoardSnapshot, DefaultInitialization) {
    ScoreBoardSnapshot snapshot;
    EXPECT_EQ(snapshot.totalScore, 0);
    EXPECT_TRUE(snapshot.frames.empty());
}

// Test: Adding a frame display to snapshot
TEST(TestScoreBoardSnapshot, AddFrameDisplay) {
    ScoreBoardSnapshot snapshot;

    FrameDisplay frame;
    frame.frameNumber = 1;
    frame.rolls = { 10 };
    frame.rawScore = 10;
    frame.bonusPoints = 10;
    frame.frameTotal = 20;
    frame.cumulativeTotal = 20;
    frame.bonusType = "Strike";

    snapshot.frames.push_back(frame);
    snapshot.totalScore = 20;

    ASSERT_EQ(snapshot.frames.size(), 1);
    EXPECT_EQ(snapshot.frames[0].frameNumber, 1);
    EXPECT_EQ(snapshot.totalScore, 20);
    EXPECT_EQ(snapshot.frames[0].bonusType, "Strike");
}

// Test: Multiple frames accumulation
TEST(TestScoreBoardSnapshot, MultipleFrames) {
    ScoreBoardSnapshot snapshot;

    int cumulative = 0;
    for (int i = 1; i <= 3; ++i) {
        FrameDisplay frame;
        frame.frameNumber = i;
        frame.rolls = { i, i };
        frame.rawScore = i * 2;
        frame.bonusPoints = 0;
        frame.frameTotal = i * 2;
        cumulative += frame.frameTotal;
        frame.cumulativeTotal = cumulative;
        snapshot.frames.push_back(frame);
        snapshot.totalScore += frame.frameTotal;
    }

    EXPECT_EQ(snapshot.frames.size(), 3);
    EXPECT_EQ(snapshot.totalScore, 12); // 2+4+6
}