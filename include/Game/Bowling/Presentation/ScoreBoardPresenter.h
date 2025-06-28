#pragma once

#include "Game/Bowling/Presentation/ScoreBoardSnapshot.h"
#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Scoring/PlayerScore.h"
#include <memory>

namespace Game::Bowling::Presentation {

    class ScoreBoardPresenter {
    public:
        static ScoreBoardSnapshot createSnapshot(
            const std::vector<std::unique_ptr<Game::Bowling::Core::Frame>>& frames,
            const Game::Bowling::Scoring::PlayerScore& scoreBoard
        );

        static void displayToConsole(const ScoreBoardSnapshot& snapshot);
    };

}
