#include "Game/Bowling/Engine/GameState.h"

using namespace Game::Bowling::Engine;

GameState::GameState()
    : gameEnded(false), currentFrameIndex(0), currentRollCount(0) {}

void GameState::advanceFrame() {
    if (currentFrameIndex >= 9) {
        gameEnded = true;
        return;
    }
    ++currentFrameIndex;
    resetRolls();
}

void GameState::incrementRoll() {
    ++currentRollCount;
}

void GameState::resetRolls() {
    currentRollCount = 0;
}

void Game::Bowling::Engine::GameState::setGameEnded(bool value)
{
    gameEnded = value;
}

bool GameState::isGameEnded() const {
    return gameEnded;
}

void GameState::markGameEnded() {
    gameEnded = true;
}

int GameState::getCurrentFrameIndex() const {
    return currentFrameIndex;
}

int GameState::getCurrentRollCount() const {
    return currentRollCount;
}
