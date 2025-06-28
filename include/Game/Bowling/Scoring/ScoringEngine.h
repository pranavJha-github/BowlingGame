#pragma once

#include <vector>
#include <memory>
#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Engine/GameState.h"
#include "Game/Bowling/Scoring/PlayerScore.h"

namespace Game::Bowling::Scoring {

    class ScoringEngine {
    public:
        virtual ~ScoringEngine() = default;

        virtual void calculateScore(
            const std::vector<std::unique_ptr<Game::Bowling::Core::Frame>>& frames,
            Game::Bowling::Engine::GameState& gameState,
            PlayerScore& playerScore
        ) = 0;
    };

} // namespace Game::Bowling::Scoring
