/**
 * @file LevelTest.cpp
 * @author Maria Pacifico
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Game.h>

/// File name for test
const std::wstring BackGroundFileName = L"images/backgroundColorDesert.png";

class LevelMock : public Level {
public:
    LevelMock(Game *game) : Level(game, BackGroundFileName) {}
};

TEST(Level, Construct)
{
    Game game;
    LevelMock level (&game);

    // Level has the same height as the game
//    ASSERT_EQ(level.GetHeight(), game.GetHeight());
}