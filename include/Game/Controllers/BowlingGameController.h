#pragma once

#include <memory>
#include "Game/Bowling/Engine/BowlingGame.h"
#include "IGameController.h"

namespace Game::Controllers {

    /*
    * A concrete controller that implements the control flow for a single bowling game.
    * Handles inputs, triggers rolls, and interacts with the Engine and Scoring layers.
    * Encapsulates business logic outside of game models.
    * Allows external UIs (CLI, GUI, web) to interact with the game through a consistent facade.
    */
    class BowlingGameController : public IGameController {
    protected:
        std::unique_ptr<Bowling::Engine::BowlingGame> game;

    public:
        BowlingGameController();

        void startGame() override;
        void roll(int pins) override;
        int getScore() const override;
        void displayScore() override;
        bool isGameOver() const override;
    };

} // namespace Game::Controllers
