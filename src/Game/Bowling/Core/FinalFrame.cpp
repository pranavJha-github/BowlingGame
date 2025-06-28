#include "Game/Bowling/Core/FinalFrame.h"
#include "Game/Bowling/Exceptions/InvalidRollException.h"
#include "Game/Bowling/Exceptions/GameOverException.h"
#include <stdexcept>

namespace Game::Bowling::Core {

    FinalFrame::FinalFrame(int number) : Frame(number) {
        rollLimit = 3;
    }

    void FinalFrame::roll(int pins) {
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
        }
        else if (rolls.size() == 2 && (rolls[0] + rolls[1] == 10)) {
            bonus = BonusType::Spare;
        }
        else {
            bonus = BonusType::None;
        }
    }

    bool FinalFrame::isComplete() const {
        if (rolls.size() < 2) return false;
        if (rolls.size() == 2 && (rolls[0] + rolls[1] < 10)) return true;
        return rolls.size() == rollLimit;
    }


    int FinalFrame::getFrameInPin() const {
        if (rolls.empty()) {
            return 10;
        }

        if (rolls.size() == 1) {
            if (rolls[0] == 10) {
                return 10; // strike on first roll; fresh 10 pins
            }
            else {
                return 10 - rolls[0];
            }
        }

        if (rolls.size() == 2) {
            // Two strikes
            if (rolls[0] == 10 && rolls[1] == 10) {
                return 10;
            }
            // Strike then non-strike
            else if (rolls[0] == 10) {
                return 10 - rolls[1];
            }
            // Spare case
            else if (rolls[0] + rolls[1] == 10) {
                return 10;
            }
            // No strike/spare; only 2 rolls allowed
            else {
                return 0;
            }
        }

        return 0; // Already had 3 rolls
    }


} // namespace Game::Bowling::Core
