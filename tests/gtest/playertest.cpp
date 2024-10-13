#include "pch.h"
#include "player.h"
#include "gameinfo.h"

class PlayerTest : public ::testing::Test {
protected:
	Player player = Player("player_username", PLAYER_STARTING_SCORE, PLAYER_STARTING_LIVES);
};

TEST_F(PlayerTest, PlayerInitNameTest) {
	std::string name_test = "player_username";
	EXPECT_EQ(player.getName(), name_test);
}

TEST_F(PlayerTest, PlayerInitScoreTest) {
	EXPECT_EQ(player.getScore(), PLAYER_STARTING_SCORE);
}

TEST_F(PlayerTest, PlayerInitLivesTest) {
	EXPECT_EQ(player.getLives(), PLAYER_STARTING_LIVES);
}

TEST_F(PlayerTest, PlayerSetNameTest) {
	std::string new_name = "new_name";
	player.setName(new_name);
	EXPECT_EQ(player.getName(), new_name);
}

TEST_F(PlayerTest, PlayerSetScoreTest) {
	player.setScore(123);
	EXPECT_EQ(player.getScore(), 123);
}

TEST_F(PlayerTest, PlayerSetLivesTest) {
	player.setLives(123);
	EXPECT_EQ(player.getLives(), 123);
}

TEST_F(PlayerTest, PlayerAddScoreTest) {
	player.setScore(111);
	EXPECT_EQ(player.getScore(), 111);
	player.addScore(12);
	EXPECT_EQ(player.getScore(), 123);
}

TEST_F(PlayerTest, PlayerUpdateLivesTest) {
	player.setLives(111);
	EXPECT_EQ(player.getLives(), 111);
	player.updateLives(-11);
	EXPECT_EQ(player.getLives(), 100);
}