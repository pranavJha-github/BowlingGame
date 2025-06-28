#include "Game/Bowling/Engine/GameState.h"
#include <gtest/gtest.h>

using namespace Game::Bowling::Engine;

TEST(TestGameState, InitiallyNotEnded) {
    GameState state;
    // Game should not be ended initially
    EXPECT_FALSE(state.isGameEnded());
}

TEST(TestGameState, SetGameEndedTrue) {
    GameState state;
    state.setGameEnded(true);
    // After setting, game should be marked as ended
    EXPECT_TRUE(state.isGameEnded());
}

TEST(TestGameState, SetGameEndedFalse) {
    GameState state;
    state.setGameEnded(true);
    state.setGameEnded(false);
    // Toggling back to false should work
    EXPECT_FALSE(state.isGameEnded());
}

// Game should not allow playing an 11th frame (i.e., more than 10 frames)
TEST(GameStateTests, ShouldNotAllowExtraFramesBeyondTen) {
    Game::Bowling::Engine::GameState gameState;
    for (int i = 0; i < 10; ++i) gameState.advanceFrame(); // 10 frames allowed
    EXPECT_TRUE(gameState.isGameEnded());

    // Try to advance one more
    gameState.advanceFrame();
    EXPECT_TRUE(gameState.isGameEnded()) << "Game must remain ended after 10 frames.";
}
