#include "Game/Bowling/Scoring/PlayerScore.h"

using namespace Game::Bowling::Scoring;

PlayerScore::PlayerScore() : totalScore(0) {
    frameScores.resize(10, 0);
}

void PlayerScore::updateFrameScore(int frameIndex, int score) {
    if (frameIndex >= 0 && frameIndex < 10) {
        frameScores[frameIndex] = score;
    }
}

int PlayerScore::getFrameScore(int frameIndex) const {
    if (frameIndex >= 0 && frameIndex < 10) {
        return frameScores[frameIndex];
    }
    return 0;
}

int PlayerScore::getTotalScore() const {
    return totalScore;
}

void PlayerScore::setTotalScore(int score) {
    totalScore = score;
}

void PlayerScore::clear() {
    std::fill(frameScores.begin(), frameScores.end(), 0);
    totalScore = 0;
}
