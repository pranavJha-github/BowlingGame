#pragma once

#include "BowlingException.h"
#include <string>

namespace Game::Bowling::Exceptions {

    class InvalidRollException : public BowlingException {
    public:
        InvalidRollException(int rolledValue, int maxAllowed)
            : BowlingException("Invalid roll: rolled " + std::to_string(rolledValue) +
                ", but maximum allowed is " + std::to_string(maxAllowed)),
            rolled(rolledValue), max(maxAllowed) {}

        int getRolledValue() const { return rolled; }
        int getMaxAllowed() const { return max; }

    private:
        int rolled;
        int max;
    };

} // namespace Game::Bowling::Exceptions
