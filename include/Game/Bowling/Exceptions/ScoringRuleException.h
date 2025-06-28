#pragma once

#include "BowlingException.h"
#include <string>

namespace Game::Bowling::Exceptions {

    class ScoringRuleException : public BowlingException {
    public:
        ScoringRuleException(const std::string& context)
            : BowlingException("Scoring rule violated: " + context) {}
    };

}
