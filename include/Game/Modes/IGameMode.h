#pragma once

namespace Game::Modes {
    
    /*
    * Abstract interface for different gameplay modes - single-player, multiplayer, team play etc.
    */
    class IGameMode {
    public:
        virtual ~IGameMode() = default;

        virtual void startGame() = 0;
        virtual void roll(int pins) = 0;
        virtual int getScore() const = 0;
        virtual void displayScore() = 0;
        virtual bool isGameOver() const = 0;
    };

} // namespace Game::Modes
