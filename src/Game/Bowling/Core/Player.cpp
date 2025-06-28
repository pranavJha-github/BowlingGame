#include "Game/Bowling/Core/Player.h"

namespace Game::Bowling::Core {

    Player::Player(const std::string& name) : name(name), maxScore(0) {}

    void Player::updateMaxScore(int score) {
        if (score > maxScore) {
            maxScore = score;
        }
    }

    const std::string& Player::getName() const
    {
        return name;
    }

    int Player::getMaxScore() const {
        return maxScore;
    }

} // namespace Game::Bowling::Core
