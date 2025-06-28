#pragma once

#include <memory>
#include "Game/Controllers/BowlingGameController.h"
#include "Game/Modes/IGameMode.h"

namespace Game::Modes {
    /*
    * SinglePlayerGame acts as a facade, exposing minimal API (startGame(), roll(pins), getScore(), isGameOver()), and delegates all orchestration to the controller.
    * SinglePlayerGame does not track game progress or scoring logic directly.
    */
    class SinglePlayerGame : public IGameMode {
    private:
        std::unique_ptr<Game::Controllers::BowlingGameController> controller;

    public:
        SinglePlayerGame();
        void startGame() override;
        void roll(int pins) override;
        int getScore() const override;
        void displayScore() override;
        bool isGameOver() const override;
    };

} // namespace Game::Modes
