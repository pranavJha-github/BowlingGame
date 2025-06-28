#pragma once

#include <vector>

namespace Game::Bowling::Scoring {

    class PlayerScore {
    private:
        std::vector<int> frameScores;
        int totalScore;

    public:
        PlayerScore();

        void updateFrameScore(int frameIndex, int score);
        int getFrameScore(int frameIndex) const;
        int getTotalScore() const;

        void setTotalScore(int score);
        void clear(); // resets scores
    };

} // namespace Game::Bowling::Scoring
