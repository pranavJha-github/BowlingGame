#include "Game/Bowling/Presentation/ScoreBoardPresenter.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Game::Bowling::Core;
using namespace Game::Bowling::Scoring;
using namespace Game::Bowling::Presentation;

ScoreBoardSnapshot ScoreBoardPresenter::createSnapshot(
    const std::vector<std::unique_ptr<Frame>>& frames,
    const PlayerScore& scoreBoard
) {
    ScoreBoardSnapshot snapshot;
    int cumulative = 0;

    for (size_t i = 0; i < frames.size(); ++i) {
        FrameDisplay frameDisplay;
        const auto& frame = frames[i];

        frameDisplay.frameNumber = static_cast<int>(i) + 1;
        frameDisplay.rolls = frame->getRolls();
        frameDisplay.rawScore = frame->getRawScore();
        frameDisplay.frameTotal = frame->getScore();  // includes bonus
        frameDisplay.bonusPoints = frameDisplay.frameTotal - frameDisplay.rawScore;

        switch (frame->getBonusType()) {
            case BonusType::Strike: frameDisplay.bonusType = "Strike"; break;
            case BonusType::Spare:  frameDisplay.bonusType = "Spare"; break;
            default: break;
        }

        cumulative += frameDisplay.frameTotal;
        frameDisplay.cumulativeTotal = cumulative;

        snapshot.frames.push_back(frameDisplay);
    }

    snapshot.totalScore = scoreBoard.getTotalScore();
    return snapshot;
}


#include <string>

void Game::Bowling::Presentation::ScoreBoardPresenter::displayToConsole(const ScoreBoardSnapshot& snapshot)
{
    using std::cout;
    using std::endl;

    cout << "\n+--------+------------+-----+------+------------+------------+-------------+\n";
    cout <<   "| Frame  |   Rolls    | Raw |Bonus | FrameTotal | Cumulative |  BonusType  |\n";
    cout <<   "+--------+------------+-----+------+------------+------------+-------------+\n";

    for (const auto& f : snapshot.frames) {
        std::ostringstream rollsStr;
        for (int r : f.rolls) {
            rollsStr << r << " ";
        }
        std::string rolls = rollsStr.str();
        if (rolls.empty()) rolls = "-";
        else rolls.pop_back(); // remove trailing space

        // Ensure rolls fit in 10 characters
        if (rolls.length() > 10) rolls = rolls.substr(0, 10);

        // Prefix frame number with * or ^ for bonus
        std::string frameLabel;
        if (f.bonusType == "Strike") frameLabel = "*" + std::to_string(f.frameNumber);
        else if (f.bonusType == "Spare") frameLabel = "^" + std::to_string(f.frameNumber);
        else frameLabel = std::to_string(f.frameNumber);

        // Format bonus type column
        std::string bonusDisplay = (f.bonusType.empty()) ? "-" : f.bonusType;

        // Main row with strict alignment
        cout << "| " << std::setw(6) << std::right << frameLabel << " "
            << "| " << std::setw(10) << std::left << rolls << " "
            << "| " << std::setw(3) << std::right << f.rawScore << " "
            << "| " << std::setw(4) << std::right << f.bonusPoints << " "
            << "| " << std::setw(10) << std::right << f.frameTotal << " "
            << "| " << std::setw(10) << std::right << f.cumulativeTotal << " "
            << "| " << std::setw(11) << std::left << bonusDisplay << " |\n";

        cout << "+--------+------------+-----+------+------------+------------+-------------+\n";
    }

    cout << "Final Score: " << snapshot.totalScore << "\n";
}