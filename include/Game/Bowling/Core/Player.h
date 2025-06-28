#pragma once

#include <string>

namespace Game {
    namespace Bowling {
        namespace Core {
            // Encapsulates player metadata (e.g., name, max score).
            class Player {
            private:
                std::string name;
                int maxScore;

            public:
                Player(const std::string& playerName);

                const std::string& getName() const;
                int getMaxScore() const;
                void updateMaxScore(int score);
            };

        }  // namespace Core
    }  // namespace Bowling
}  // namespace Game
