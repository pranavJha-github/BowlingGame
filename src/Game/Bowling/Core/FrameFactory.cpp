#include "Game/Bowling/Core/FrameFactory.h"
#include "Game/Bowling/Core/FinalFrame.h"

namespace Game::Bowling::Core {

    std::unique_ptr<Frame> FrameFactory::createFrame(int index) {
        if (index == 10) {
            return std::make_unique<FinalFrame>(index);  // FinalFrame for 10th
        }
        return std::make_unique<Frame>(index);
    }

} // namespace Game::Bowling::Core
