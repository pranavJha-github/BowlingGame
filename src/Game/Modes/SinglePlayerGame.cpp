#include "Game/Modes/SinglePlayerGame.h"

using namespace Game::Modes;
using namespace Game::Controllers;

SinglePlayerGame::SinglePlayerGame()
    : controller(std::make_unique<BowlingGameController>()) {}

void SinglePlayerGame::startGame() {
    controller->startGame();
}

void SinglePlayerGame::roll(int pins) {
    controller->roll(pins);
}

int SinglePlayerGame::getScore() const {
    return controller->getScore();
}

void Game::Modes::SinglePlayerGame::displayScore()
{
    controller->displayScore();
}

bool SinglePlayerGame::isGameOver() const {
    return controller->isGameOver();
}
