#include "Game/Bowling/Engine/BowlingGame.h"
#include "Game/Bowling/Scoring/StandardBowlingScoring.h"
#include "Game/Bowling/Exceptions/GameOverException.h"
#include "Game/Bowling/Exceptions/InvalidRollException.h"
#include "Game/Bowling/Exceptions/TooManyRollsException.h"
#include "Game/Bowling/Presentation/ScoreBoardPresenter.h"

using namespace Game::Bowling::Engine;
using namespace Game::Bowling::Core;
using namespace Game::Bowling::Exceptions;
using namespace Game::Bowling::Scoring;

BowlingGame::BowlingGame()
    : player("Player1"),
    scoringEngine(std::make_unique<StandardBowlingScoring>()),
    frameFactory(std::make_unique<FrameFactory>()) {}

void BowlingGame::roll(int pins) {
    int frameIndex = state.getCurrentFrameIndex();

    // Allow FinalFrame to handle invalid roll, if it's not truly over
    if (state.isGameEnded() && (frameIndex < 9 || (frameIndex == 9 && frames[frameIndex] && frames[frameIndex]->isComplete()))) {
        throw GameOverException();
    }

    // Ensure frame exists
    if (frames.size() <= frameIndex) {
        frames.push_back(frameFactory->createFrame(frameIndex + 1)); // 1-based
    }

    Frame* currentFrame = frames[frameIndex].get();

    if (currentFrame->isComplete()) {
        frameIndex++;
        if (frameIndex >= 10) {
            throw TooManyRollsException(frameIndex + 1, pins);
        }

        state.advanceFrame();
        frames.push_back(frameFactory->createFrame(frameIndex + 1));
        currentFrame = frames[frameIndex].get(); // Refresh after push
    }

    currentFrame->roll(pins);

    scoringEngine->calculateScore(frames, state, scoreBoard);

    // Final game over check — call only when actual FinalFrame is fully done
    if (frames.size() == 10 && frames[9] && frames[9]->isComplete()) {
        state.markGameEnded();
    }
}


int BowlingGame::getTotalScore() const {
    return scoreBoard.getTotalScore();
}

Game::Bowling::Presentation::ScoreBoardSnapshot Game::Bowling::Engine::BowlingGame::getScoreSnapshot() const
{
    return Game::Bowling::Presentation::ScoreBoardPresenter::createSnapshot(frames, scoreBoard);
}

bool BowlingGame::isGameOver() const {
    return state.isGameEnded();
}
