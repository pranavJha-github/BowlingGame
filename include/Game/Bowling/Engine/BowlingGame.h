#pragma once

#include <vector>
#include <memory>
#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Core/FinalFrame.h"
#include "Game/Bowling/Core/FrameFactory.h"
#include "Game/Bowling/Core/Player.h"
#include "Game/Bowling/Engine/GameState.h"
#include "Game/Bowling/Scoring/ScoringEngine.h"
#include "Game/Bowling/Scoring/PlayerScore.h"
#include "Game/Bowling/Presentation/ScoreBoardSnapshot.h"

namespace Game::Bowling::Engine {

    class BowlingGame {
    protected:
        Core::Player player;
        std::vector<std::unique_ptr<Core::Frame>> frames;
        std::unique_ptr<Scoring::ScoringEngine> scoringEngine;
        GameState state;
        Scoring::PlayerScore scoreBoard;
        std::unique_ptr<Core::FrameFactory> frameFactory;
        
    public:
        BowlingGame();

        void roll(int pins);
        int getTotalScore() const;
        Game::Bowling::Presentation::ScoreBoardSnapshot getScoreSnapshot() const;
        bool isGameOver() const;
        const std::vector<std::unique_ptr<Core::Frame>>& getFrames() const { return frames; }
    };

} // namespace Game::Bowling::Engine
