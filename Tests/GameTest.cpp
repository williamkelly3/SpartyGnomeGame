#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filename.h>
#include <Game.h>
#include <Item.h>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

class GameTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath() {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/game";
        if (!wxFileName::DirExists(path)) {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }

    /**
   * Test to ensure a game .aqua file is empty
   */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<game/>")));

    }

};

TEST_F(GameTest, Construct){
    Game game;
}

TEST(ItemTest, HitTest) {
    // Create a fish to test
    Game game;
    ItemMock item(&game);

    // Give it a location
    // Always make the numbers different, in case they are mixed up
    item.SetLocation(100, 200);

    // Center of the fish should be a true
    ASSERT_TRUE(item.CollisionTest(100, 200));

    // Left of the fish
    ASSERT_FALSE(item.CollisionTest(10, 200));

    // Right of the fish
    ASSERT_FALSE(item.CollisionTest(200, 200));

    // Above the fish
    ASSERT_FALSE(item.HitTest(100, 0));

    // Below the fish
    ASSERT_FALSE(item.HitTest(100, 300));

    // On a fish transparent pixel
    ASSERT_FALSE(item.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16));
}

TEST_F(GameTest, CollisionTest) {
    Game aquarium;

    ASSERT_EQ(aquarium.CollisionTest(100, 200), nullptr) <<
                                                   L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.CollisionTest(100, 200) == fish1) <<
                                                     L"Testing fish at 100, 200";

    // Test to ensure nullptr if we hit away from any image
    ASSERT_EQ(aquarium.CollisionTest(0, 200), nullptr) << L"Testing fish at 00, 200";

    // Add two overlapping fish
    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(400, 400);

    shared_ptr<FishBeta> fish3 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish3);
    fish3->SetLocation(400, 400);

    // Ensure the top one is found
    ASSERT_EQ(aquarium.CollisionTest(400, 400), fish3) << L"Testing overlapping fish";

}

