#pragma once

#include <vector>
#include <string>

namespace Game::Bowling::Presentation {

    struct FrameDisplay {
        int frameNumber;
        std::vector<int> rolls;
        int rawScore = 0;
        int bonusPoints = 0;
        int frameTotal = 0;
        int cumulativeTotal = 0;
        std::string bonusType;
    };

    struct ScoreBoardSnapshot {
        std::vector<FrameDisplay> frames;
        int totalScore = 0;
    };

}
