#pragma once
#include <memory>
#include "Game/Bowling/Core/Frame.h"

namespace Game::Bowling::Core {

    // Creates either a Frame or a FinalFrame based on the frame index (1-9 vs. 10).
    class FrameFactory {
    public:
        std::unique_ptr<Frame> createFrame(int index);
    };

} // namespace Game::Bowling::Core
