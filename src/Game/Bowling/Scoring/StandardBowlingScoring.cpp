#include "Game/Bowling/Scoring/StandardBowlingScoring.h"
#include "Game/Bowling/Core/Frame.h"

using namespace Game::Bowling::Core;
using namespace Game::Bowling::Engine;
using namespace Game::Bowling::Scoring;

void StandardBowlingScoring::calculateScore(
    const std::vector<std::unique_ptr<Frame>>& frames,
    GameState& gameState,
    PlayerScore& playerScore
) {
    int total = 0;
    playerScore.clear();

    if (frames.empty()) return;

    // Step 1: Reset bonus state
    for (auto& frame : frames) {
        frame->resetBonus();
    }

    // Step 2: Apply bonus cleanly
    for (size_t i = 0; i < frames.size(); ++i) {
        auto& frame = frames[i];
        BonusType bonus = frame->getBonusType();

        if (bonus == BonusType::Spare) {
            auto bonusRolls = getNextNRollsAfterFrame(i, 1, frames);
            if (!bonusRolls.empty()) {
                frame->addBonus(bonusRolls[0]);
            }
        }
        else if (bonus == BonusType::Strike) {
            auto bonusRolls = getNextNRollsAfterFrame(i, 2, frames);
            for (size_t j = 0; j < bonusRolls.size(); ++j) {
                frame->addBonus(bonusRolls[j]);
            }
        }
    }

    // Step 3: Compute total and per-frame scores
    for (size_t i = 0; i < frames.size(); ++i) {
        int score = frames[i]->getScore();
        playerScore.updateFrameScore(static_cast<int>(i), score);
        total += score;
    }

    playerScore.setTotalScore(total);

    if (frames.size() == 10 && frames.back()->isComplete()) {
        gameState.setGameEnded(true);
    }
}

std::vector<int> Game::Bowling::Scoring::StandardBowlingScoring::getNextNRollsAfterFrame(size_t frameIndex, int count, const std::vector<std::unique_ptr<Frame>>& frames)
{
    std::vector<int> nextRolls;
    for (size_t i = frameIndex + 1; i < frames.size() && nextRolls.size() < count; ++i) {
        const auto& rolls = frames[i]->getRolls();
        for (int r : rolls) {
            nextRolls.push_back(r);
            if (nextRolls.size() == count) break;
        }
    }
    return nextRolls;
}

