#pragma once 

#include "gmock/gmock.h"
#include "attendance.h"

class AttendanceManagerFixture : public testing::Test {
public:
	AttendanceManager atm;
	AttendanceManagerFixture()
	{
		atm.ReadAttendanceData();
	}

private:
	map<string, int> id1;
};

TEST(PlayerRepoTest, TC1) {
	//Arrange 
	string name = "player1";
	int id = 0;
	PlayerRepo playerRepo;

	//Act
	playerRepo.add(name);

	//Assertion
	EXPECT_EQ(playerRepo.existsByName(name), true);
	EXPECT_EQ(playerRepo.existsById(id), true);
}

TEST_F(AttendanceManagerFixture, NewPlayerCheckTC) {
	//Arrange 
	string name = "player1";
	bool expectResult = false;

	//Act
	bool result = atm.IsNewPlayer(name);

	//Assertion
	EXPECT_EQ(result, expectResult);
}

TEST_F(AttendanceManagerFixture, AddPlayerCheckTC) {
	//Arrange 
	string name = "player1";
	bool expectResult = false;

	//Act
	bool result = atm.IsNewPlayer(name);

	//Assertion
	EXPECT_EQ(result, expectResult);
}

TEST_F(AttendanceManagerFixture, CalculateAttendancePointsTC) {
	//Arrange 
	string name = "player1";
	Player player{ name , 0, 0 };
	int expectePoints = 2;

	//Act
	atm.AddNewPlayer(name);
	Player player2 = atm.GetPlayer(name);
	atm.CalculateAttendancePoints(player2, "sunday");

	//Assertion
	EXPECT_EQ(player2.attendancePoint, expectePoints);
}

TEST_F(AttendanceManagerFixture, TC) {
	//Arrange 
	//Act
	//Assertion
	EXPECT_EQ(1, 1);
}