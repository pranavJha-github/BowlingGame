#pragma once
#include <vector>

namespace Game::Bowling::Core {

    enum class BonusType {
        None,
        Spare,
        Strike
    };

    /*
    * Base class for all bowling frames.
    * Tracks roll values, frame number, score, and bonus status (Normal, Spare, Strike).
    */
    class Frame {
    protected:
        int frameNumber;
        std::vector<int> rolls;
        int rollLimit;
        int score;
        BonusType bonus;
        int bonusRollsToAdd = 0;
        int pendingBonusPoints = 0;

    public:
        explicit Frame(int number);
        virtual ~Frame() = default;

        // To be overriden in FinalFrame
        virtual void roll(int pins);
        virtual int getFrameInPin() const;
        virtual bool isComplete() const;

        int getScore() const;
        bool isScoringComplete() const;
        void addBonus(int pins);
        void resetBonus();
        const std::vector<int>& getRolls() const { return rolls; }
        BonusType getBonusType() const { return bonus; }
        int getFrameNumber() const { return frameNumber; }
        int getRawScore() const { return score; }
    };

} // namespace Game::Bowling::Core
