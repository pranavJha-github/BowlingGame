#include <gtest/gtest.h>
#include <memory>
#include "Game/Bowling/Scoring/StandardBowlingScoring.h"
#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Core/FinalFrame.h"
#include "Game/Bowling/Engine/GameState.h"
#include "Game/Bowling/Scoring/PlayerScore.h"

using namespace Game::Bowling::Scoring;
using namespace Game::Bowling::Core;
using namespace Game::Bowling::Engine;

// Helper to create a frame with rolls
std::unique_ptr<Frame> makeFrame(int frameNum, const std::vector<int>& pins) {
    auto f = std::make_unique<Frame>(frameNum);
    for (int pin : pins) f->roll(pin);
    return f;
}

// Test: Score is computed correctly for a spare
TEST(StandardBowlingScoringTest, SpareBonusAddsNextRoll) {
    std::vector<std::unique_ptr<Frame>> frames;
    frames.push_back(makeFrame(1, { 5, 5 })); // Spare
    frames.push_back(makeFrame(2, { 4, 2 }));

    GameState state;
    PlayerScore score;
    StandardBowlingScoring scorer;
    scorer.calculateScore(frames, state, score);

    EXPECT_EQ(score.getTotalScore(), 5 + 5 + 4 + 4 + 2); // 20
    EXPECT_EQ(score.getFrameScore(0), 14);
    EXPECT_EQ(score.getFrameScore(1), 6);
}

// Test: Score is computed correctly for a strike
TEST(StandardBowlingScoringTest, StrikeBonusAddsNextTwoRolls) {
    std::vector<std::unique_ptr<Frame>> frames;
    frames.push_back(makeFrame(1, { 10 })); // Strike
    frames.push_back(makeFrame(2, { 4, 2 }));

    GameState state;
    PlayerScore score;
    StandardBowlingScoring scorer;
    scorer.calculateScore(frames, state, score);

    EXPECT_EQ(score.getTotalScore(), 10 + 4 + 2 + 4 + 2); // 22
    EXPECT_EQ(score.getFrameScore(0), 16);
    EXPECT_EQ(score.getFrameScore(1), 6);
}

// Test: Multiple strikes in sequence
TEST(StandardBowlingScoringTest, MultipleStrikesChainCorrectly) {
    std::vector<std::unique_ptr<Frame>> frames;
    frames.push_back(makeFrame(1, { 10 }));
    frames.push_back(makeFrame(2, { 10 }));
    frames.push_back(makeFrame(3, { 10 }));
    frames.push_back(makeFrame(4, { 3, 2 }));

    GameState state;
    PlayerScore score;
    StandardBowlingScoring scorer;
    scorer.calculateScore(frames, state, score);

    EXPECT_EQ(score.getFrameScore(0), 10 + 10 + 10); // 30
    EXPECT_EQ(score.getFrameScore(1), 10 + 10 + 3);  // 23
    EXPECT_EQ(score.getFrameScore(2), 10 + 3 + 2);   // 15
    EXPECT_EQ(score.getFrameScore(3), 5);
    EXPECT_EQ(score.getTotalScore(), 30 + 23 + 15 + 5); // 73
}

// Test: Game ends after 10 frames and scoring is marked complete
TEST(StandardBowlingScoringTest, GameEndsAfterTenFrames) {
    std::vector<std::unique_ptr<Frame>> frames;
    for (int i = 1; i <= 10; ++i) {
        frames.push_back(makeFrame(i, { 4, 5 }));
    }

    GameState state;
    PlayerScore score;
    StandardBowlingScoring scorer;
    scorer.calculateScore(frames, state, score);

    EXPECT_TRUE(state.isGameEnded());
    EXPECT_EQ(score.getTotalScore(), 9 * 10); // 90
}

TEST(ScoringTests, AllSparesShouldResultIn150Score) {
    using namespace Game::Bowling;

    std::vector<std::unique_ptr<Core::Frame>> frames;
    for (int i = 1; i <= 9; ++i) {
        auto f = std::make_unique<Core::Frame>(i);
        f->roll(5); f->roll(5);  // spare
        frames.push_back(std::move(f));
    }

    auto last = std::make_unique<Core::FinalFrame>(10);
    last->roll(5); last->roll(5); last->roll(5);  // spare + bonus
    frames.push_back(std::move(last));

    Engine::GameState state;
    Scoring::PlayerScore score;
    Scoring::StandardBowlingScoring scoring;

    scoring.calculateScore(frames, state, score);
    EXPECT_EQ(score.getTotalScore(), 150);
}

TEST(ScoringTests, AllZerosShouldResultInZeroScore) {
    using namespace Game::Bowling;

    std::vector<std::unique_ptr<Core::Frame>> frames;
    for (int i = 1; i <= 9; ++i) {
        auto f = std::make_unique<Core::Frame>(i);
        f->roll(0); f->roll(0);
        frames.push_back(std::move(f));
    }

    auto last = std::make_unique<Core::FinalFrame>(10);
    last->roll(0); last->roll(0);
    frames.push_back(std::move(last));

    Engine::GameState state;
    Scoring::PlayerScore score;
    Scoring::StandardBowlingScoring scoring;

    scoring.calculateScore(frames, state, score);
    EXPECT_EQ(score.getTotalScore(), 0);
}

TEST(ScoringTests, PerfectGameShouldScore300) {
    using namespace Game::Bowling;

    std::vector<std::unique_ptr<Core::Frame>> frames;
    for (int i = 1; i <= 9; ++i) {
        auto f = std::make_unique<Core::Frame>(i);
        f->roll(10);
        frames.push_back(std::move(f));
    }

    auto last = std::make_unique<Core::FinalFrame>(10);
    last->roll(10); last->roll(10); last->roll(10);
    frames.push_back(std::move(last));

    Engine::GameState state;
    Scoring::PlayerScore score;
    Scoring::StandardBowlingScoring scoring;

    scoring.calculateScore(frames, state, score);
    EXPECT_EQ(score.getTotalScore(), 300);
}

TEST(ScoringTests, StrikeThenSpareInLastFramesShouldCalculateCorrectly) {
    using namespace Game::Bowling;

    std::vector<std::unique_ptr<Core::Frame>> frames;
    for (int i = 1; i <= 8; ++i) {
        auto f = std::make_unique<Core::Frame>(i);
        f->roll(4); f->roll(4);  // 8 per frame
        frames.push_back(std::move(f));
    }

    auto f9 = std::make_unique<Core::Frame>(9);
    f9->roll(10); // strike
    frames.push_back(std::move(f9));

    auto last = std::make_unique<Core::FinalFrame>(10);
    last->roll(5); last->roll(5); last->roll(7);  // spare + bonus
    frames.push_back(std::move(last));

    Engine::GameState state;
    Scoring::PlayerScore score;
    Scoring::StandardBowlingScoring scoring;

    scoring.calculateScore(frames, state, score);
    EXPECT_EQ(score.getTotalScore(), (8 * 8) + 20 + 17);  // 64 + 20 + 17 = 101
}

