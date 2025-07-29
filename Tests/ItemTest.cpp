/**
 * @file ItemTest.cpp
 * @author Maria Pacifico
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>
#include <ItemDec.h>

/// File name for test
const std::wstring FileName = L"UofM.png";
const std::wstring& id = L"i012";
ItemDec input = ItemDec(id, FileName);

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game, &input, 0, 0) {}

    void Draw(wxDC *dc) {}

    //bool CollisionTest(Item *item);
};

TEST(ItemTest, Construct) {
    Game game;
    ItemMock item(&game);
    ItemMock item2(&game);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second location with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);

    item2.SetLocation(-72, -107);
    ASSERT_TRUE(item.CollisionTest(&item2));

    item2.SetLocation(100, 123);
    ASSERT_FALSE(item.CollisionTest(&item2));
}

TEST(ItemTest, HitTest) {
    // Create a fish to test
    Game game;
    ItemMock item(&game);

    ItemMock item2(&game);
    // Give it a location
    // Always make the numbers different, in case they are mixed up
    item.SetLocation(100, 200);
    item2.SetLocation(100, 200);


    // Center of the fish should be a true
    ASSERT_TRUE(item2.CollisionTest(item*));

    // Left of the fish
    ASSERT_FALSE(item.CollisionTest(10, 200));

    // Right of the fish
    ASSERT_FALSE(item.CollisionTest(200, 200));

    // Above the fish
    ASSERT_FALSE(item.CollisionTest(100, 0));

    // Below the fish
    ASSERT_FALSE(item.CollisionTest(100, 300));

    // On a fish transparent pixel
    ASSERT_FALSE(item.CollisionTest(100 - 125/2 + 17, 200 - 117/2 + 16));
}

