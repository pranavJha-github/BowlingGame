#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Exceptions/InvalidRollException.h"
#include "Game/Bowling/Exceptions/GameOverException.h"

namespace Game::Bowling::Core {

    Frame::Frame(int number)
        : frameNumber(number), rollLimit(2), score(0), bonus(BonusType::None) {}

    void Frame::roll(int pins) {
        if (isComplete()) {
            throw Game::Bowling::Exceptions::GameOverException();
        }

        if (pins > getFrameInPin()) {
            throw Game::Bowling::Exceptions::InvalidRollException(pins, getFrameInPin());
        }


        rolls.push_back(pins);
        score += pins;

        if (rolls.size() == 1 && pins == 10) {
            bonus = BonusType::Strike;
            bonusRollsToAdd = 2;
        }
        else if (rolls.size() == 2 && score == 10) {
            bonus = BonusType::Spare;
            bonusRollsToAdd = 1;
        }
    }

    int Frame::getFrameInPin() const
    {
        int sum = 0;
        for (int pin : rolls) {
            sum += pin;
        }
        return 10 - sum;
    }

    bool Frame::isComplete() const {
        return rolls.size() >= rollLimit || bonus == BonusType::Strike;
    }

    int Frame::getScore() const {
        return score + pendingBonusPoints;
    }

    bool Frame::isScoringComplete() const
    {
        return isComplete() && bonusRollsToAdd == 0;
    }

    void Frame::addBonus(int pins)
    {
        if (bonusRollsToAdd > 0) {
            pendingBonusPoints += pins;
            bonusRollsToAdd--;
        }
    }

    void Frame::resetBonus() {
        pendingBonusPoints = 0;
        bonusRollsToAdd = (bonus == BonusType::Strike) ? 2 :
                          (bonus == BonusType::Spare)  ? 1 : 0;
    }

} // namespace Game::Bowling::Core
