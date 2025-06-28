#include "Game/Modes/SinglePlayerGame.h"
#include <iostream>
#include <memory>

using namespace Game::Modes;

int main() {
    std::unique_ptr<IGameMode> game = std::make_unique<SinglePlayerGame>();

    game->startGame();
    int pins;

    while (!game->isGameOver()) {
        std::cout << "Enter pins knocked down: ";
        std::cin >> pins;

        try {
            game->roll(pins);
            game->displayScore();
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "Game Over! Final Score: " << game->getScore() << "\n";
    return 0;
}
