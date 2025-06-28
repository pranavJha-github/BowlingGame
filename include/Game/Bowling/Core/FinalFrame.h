#pragma once
#include "Game/Bowling/Core/Frame.h"

namespace Game::Bowling::Core {

    /*
    * Overrides roll logic to allow up to 3 rolls and handle final-frame-specific rules 
    * (e.g., bonus rolls after strike/spare).
    */
    class FinalFrame : public Frame {
    public:
        explicit FinalFrame(int number);
        void roll(int pins) override;
        bool isComplete() const override;
        int getFrameInPin() const override;
    };

} // namespace Game::Bowling::Core
