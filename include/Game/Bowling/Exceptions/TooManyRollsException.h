#pragma once

#include "BowlingException.h"
#include <string>

namespace Game::Bowling::Exceptions {

    class TooManyRollsException : public BowlingException {
    public:
        TooManyRollsException(int frameIndex, int attemptedRoll)
            : BowlingException("Too many rolls in frame " + std::to_string(frameIndex) +
                ". Roll #" + std::to_string(attemptedRoll) + " is invalid.") {}
    };

}
