#include "Game/Controllers/BowlingGameController.h"
#include "Game/Bowling/Presentation/ScoreBoardPresenter.h"

using namespace Game::Controllers;
using namespace Game::Bowling::Engine;

BowlingGameController::BowlingGameController()
    : game(std::make_unique<BowlingGame>()) {}

void BowlingGameController::startGame() {
    // Future use: reset or initialize game
}

void BowlingGameController::roll(int pins) {
    game->roll(pins);
}

int BowlingGameController::getScore() const {
    return game->getTotalScore();
}

void Game::Controllers::BowlingGameController::displayScore()
{
    auto snapshot = game->getScoreSnapshot();
    Game::Bowling::Presentation::ScoreBoardPresenter::displayToConsole(snapshot);
}

bool BowlingGameController::isGameOver() const {
    return game->isGameOver();
}
