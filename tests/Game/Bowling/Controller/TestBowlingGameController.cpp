#include "Game/Controllers/BowlingGameController.h"
#include "Game/Bowling/Core/Frame.h"
#include "Game/Bowling/Engine/GameState.h"
#include "Game/Bowling/Scoring/PlayerScore.h"
#include "Game/Bowling/Scoring/StandardBowlingScoring.h"
#include "Game/Bowling/Presentation/ScoreBoardPresenter.h"
#include "Game/Bowling/Presentation/ScoreBoardSnapshot.h"

#include <gtest/gtest.h>
#include <memory>

using namespace Game::Controllers;
using namespace Game::Bowling::Core;
using namespace Game::Bowling::Scoring;
using namespace Game::Bowling::Presentation;

// Test class for mocking or extending behavior if needed
class TestableBowlingGameController : public BowlingGameController {
public:
    using BowlingGameController::BowlingGameController;
    const std::vector<std::unique_ptr<Frame>>& getFrames() const {
        return game->getFrames();
    }
};

TEST(TestBowlingGameController, GameInitializesWithEmptyFrames) {
    TestableBowlingGameController controller;
    EXPECT_EQ(controller.getFrames().size(), 0); // Initially, no frames
}

TEST(TestBowlingGameController, GameRollAddsFramesAndPins) {
    TestableBowlingGameController controller;
    controller.roll(4);
    ASSERT_EQ(controller.getFrames().size(), 1);
    EXPECT_EQ(controller.getFrames()[0]->getRolls()[0], 4);
}

TEST(TestBowlingGameController, StrikeCreatesNewFrame) {
    TestableBowlingGameController controller;
    controller.roll(10); // Strike ends frame
    EXPECT_EQ(controller.getFrames().size(), 1);
    EXPECT_TRUE(controller.getFrames()[0]->isComplete());
}

TEST(TestBowlingGameController, MultipleRollsWorkAsExpected) {
    TestableBowlingGameController controller;
    controller.roll(3);
    controller.roll(6);
    ASSERT_EQ(controller.getFrames().size(), 1);
    const auto& rolls = controller.getFrames()[0]->getRolls();
    ASSERT_EQ(rolls.size(), 2);
    EXPECT_EQ(rolls[0], 3);
    EXPECT_EQ(rolls[1], 6);
}