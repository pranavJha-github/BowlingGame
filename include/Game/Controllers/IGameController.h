#pragma once

namespace Game::Controllers {

    /*
    * An interface representing the control layer of a game instance.
    * It ensures that all game controllers (e.g., Bowling, Chess, Multiplayer Bowling)
    * follow a common start–roll–score–end lifecycle.
    */
    class IGameController {
    public:
        virtual ~IGameController() = default;

        virtual void startGame() = 0;
        virtual void roll(int pins) = 0;
        virtual int getScore() const = 0;
        virtual void displayScore() = 0;
        virtual bool isGameOver() const = 0;
    };

}
