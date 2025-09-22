#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>

using namespace std;

static const std::array<std::string, 1> trainingDays = {
	"wednesday"
};

static const std::array<std::string, 2> weekends = {
	"saturday", "sunday"
};

static const std::array<std::string, 4> weekdays= {
	"monday", "tuesday", "thursday", "friday"
};

std::map<std::string, int> attendanceScoreByDay = {
	{"monday", 1},
	{"tuesday", 1},
	{"wednesday", 3},
	{"thursday", 1},
	{"friday", 1},
	{"saturday", 2},
	{"sunday", 2}
};

bool IsTrainingDay(string input) {
	return std::find(trainingDays.begin(), trainingDays.end(), input) != trainingDays.end();
}

bool IsWeekend(string input) {
	return std::find(weekends.begin(), weekends.end(), input) != weekends.end();
}

bool IsWeekday(string input) {
	return std::find(weekdays.begin(), weekdays.end(), input) != weekdays.end();
}

enum class Day {
	monday,     // 0
	tuesday,    // 1
	wednesday,  // 2
	thursday,   // 3
	friday,     // 4
	saturday,   // 5
	sunday      // 6
};

enum class PointCategory {
	Weekdays = 0,    // 0
	Weekends = 1,    // 1
	TrainnigDay = 2, // 2
};

constexpr std::array<PointCategory, 3> PointDays = {
	PointCategory::Weekdays, PointCategory::Weekends, PointCategory::TrainnigDay
};

constexpr int PointCategoryCount = PointDays.size();


constexpr int GOLD_MEMBER = 1;
constexpr int SILVER_MBMBER = 2;
constexpr int NORMAL_MEMBER = 3;

constexpr int GOLD_ATTENDANCE_POINT = 50;
constexpr int SILVER_ATTENDANCE_POINT = 30;

constexpr int WEEKDAY_ATTENDANCE_POINT = 1;
constexpr int WEEKEND_ATTENDANCE_POINT = 2;
constexpr int TRINNINGDAY_ATTENDANCE_POINT = 3;

constexpr int WEEKEND_BONUS_ATTENDANCE_COUNT = 10;
constexpr int TRINNINGDAY_BONUS_ATTENDANCE_COUNT = 10;
constexpr int WEEKEND_BONUS_ATTENDANCE_POINT = 10;
constexpr int TRINNINGDAY_BONUS_ATTENDANCE_POINT = 10;

constexpr int MAX_PLAYER_COUNT = 100;

struct Node {
	string attendantName;
	string attendanceDay;
};

map<string, int> id1;
int totalPlayerCount = 0;

//dat[사용자ID][요일]
int attendanceCountPerDay[MAX_PLAYER_COUNT][PointCategoryCount];
int attendancePoints[MAX_PLAYER_COUNT];
int grade[MAX_PLAYER_COUNT];
string names[MAX_PLAYER_COUNT];

int trainningDay[MAX_PLAYER_COUNT];
int weekend[MAX_PLAYER_COUNT];

int assignPlayerId(string attendantName, string attendDay) {
	//ID 부여
	if (id1.count(attendantName) == 0) {
		id1.insert({ attendantName, ++totalPlayerCount });

		if (attendantName == "Daisy") {
			int debug = 1;
		}

		names[totalPlayerCount] = attendantName;
	}
	//디버깅용
	if (attendantName == "Daisy") {
		int debug = 1;
	}
	return id1[attendantName];
}

void CalculateAttendancePoints(int attendantId, string attendanceDay) {
	int add_point = 0;
	int pointsCategoryIndex = -1;
	if (IsTrainingDay(attendanceDay))
	{
		add_point += TRINNINGDAY_ATTENDANCE_POINT;
		pointsCategoryIndex = static_cast<int>(PointCategory::TrainnigDay);
		trainningDay[attendantId] += 1;
	}
	else if (IsWeekend(attendanceDay))
	{
		add_point += WEEKEND_ATTENDANCE_POINT;
		pointsCategoryIndex = static_cast<int>(PointCategory::Weekends);
		weekend[attendantId] += 1;
	}
	else if (IsWeekday(attendanceDay))
	{
		add_point += WEEKDAY_ATTENDANCE_POINT;
		pointsCategoryIndex = static_cast<int>(PointCategory::Weekdays);
	}
	else {
		return;
	}

	//사용자ID별 요일 데이터에 1씩 증가
	attendanceCountPerDay[attendantId][pointsCategoryIndex] += 1;
	attendancePoints[attendantId] += add_point;
}

bool IsRemovedPlayer(int playerId) {
	return (grade[playerId] != 1 && grade[playerId] != 2 && trainningDay[playerId] == 0 && weekend[playerId] == 0);
}

void PrintRemovedPlayer() {
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int PlayerID = 1; PlayerID <= totalPlayerCount; PlayerID++) {
		if (IsRemovedPlayer(PlayerID) == true) {
			std::cout << names[PlayerID] << "\n";
		}
	}
}

void CalculateBonusPoint() {
	for (int i = 1; i <= totalPlayerCount; i++) {
		if (attendanceCountPerDay[i][static_cast<int>(PointCategory::TrainnigDay)] >= TRINNINGDAY_BONUS_ATTENDANCE_COUNT) {
			attendancePoints[i] += TRINNINGDAY_BONUS_ATTENDANCE_POINT;
		}

		if (attendanceCountPerDay[i][static_cast<int>(PointCategory::Weekends)] >= WEEKEND_BONUS_ATTENDANCE_COUNT) {
			attendancePoints[i] += WEEKEND_BONUS_ATTENDANCE_POINT;
		}
	}
}

void GradeAttendant() {
	for (int playerIndex = 1; playerIndex <= totalPlayerCount; playerIndex++) {
		if (attendancePoints[playerIndex] >= GOLD_ATTENDANCE_POINT) {
			grade[playerIndex] = 1;
		}
		else if (attendancePoints[playerIndex] >= SILVER_ATTENDANCE_POINT) {
			grade[playerIndex] = 2;
		}
		else {
			grade[playerIndex] = 0;
		}
	}
}

void PrintAttendantPoints() {
	for (int playerIndex = 1; playerIndex <= totalPlayerCount; playerIndex++) {
		cout << "NAME : " << names[playerIndex] << ", ";
		cout << "POINT : " << attendancePoints[playerIndex] << ", ";
		cout << "GRADE : ";

		if (grade[playerIndex] == GOLD_MEMBER) {
			cout << "GOLD" << "\n";
		}
		else if (grade[playerIndex] == SILVER_MBMBER) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}
}

void ReadAttendanceData() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
//	ifstream fin{ "attendance_umar.txt" }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string attendantName, attendDay;
		fin >> attendantName >> attendDay;
		auto attendantId = assignPlayerId(attendantName, attendDay);
		CalculateAttendancePoints(attendantId, attendDay);
	}
}

int main() {
	ReadAttendanceData();
	CalculateBonusPoint();
	GradeAttendant();
	PrintAttendantPoints();
	PrintRemovedPlayer();
}