#pragma once

namespace Game::Bowling::Engine {

    class GameState {
    private:
        bool gameEnded;
        int currentFrameIndex;
        int currentRollCount;

    public:
        GameState();

        void advanceFrame();
        void incrementRoll();
        void resetRolls();

        void setGameEnded(bool value);
        bool isGameEnded() const;
        void markGameEnded();

        int getCurrentFrameIndex() const;
        int getCurrentRollCount() const;
    };

} // namespace Game::Bowling::Engine
