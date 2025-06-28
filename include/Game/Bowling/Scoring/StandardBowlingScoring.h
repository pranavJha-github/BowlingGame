#pragma once

#include "ScoringEngine.h"

namespace Game::Bowling::Scoring {

    class StandardBowlingScoring : public ScoringEngine {
    public:
        void calculateScore(
            const std::vector<std::unique_ptr<Game::Bowling::Core::Frame>>& frames,
            Game::Bowling::Engine::GameState& gameState,
            PlayerScore& playerScore
        ) override;
    private:
        static std::vector<int> getNextNRollsAfterFrame(
            size_t frameIndex,
            int count,
            const std::vector<std::unique_ptr<Game::Bowling::Core::Frame>>& frames);
    };

} // namespace Game::Bowling::Scoring

