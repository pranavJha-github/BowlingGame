#pragma once

#include "BowlingException.h"
#include <string>

namespace Game::Bowling::Exceptions {

    class GameOverException : public BowlingException {
    public:
        GameOverException()
            : BowlingException("Action not allowed: the game has already ended.") {}
    };

}
