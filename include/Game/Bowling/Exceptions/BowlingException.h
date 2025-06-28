#pragma once
#include <stdexcept>
#include <string>

namespace Game::Bowling::Exceptions {

    class BowlingException : public std::runtime_error {
    public:
        explicit BowlingException(const std::string& message)
            : std::runtime_error("BowlingException: " + message) {}
    };

} // namespace Game::Bowling::Exceptions
