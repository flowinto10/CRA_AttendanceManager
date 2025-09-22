#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>

using namespace std;

struct Player {
	std::string name;
	int id;
	int attendancePoint;
};

class PlayerRepo {
public:
	void add(string name) { 
		Player p{ name , nextPlayerId++ };
		players.push_back(std::move(p)); 
	}

	bool existsByName(const std::string& name) const {
		return std::any_of(players.begin(), players.end(),
			[&](const Player& p) { return p.name == name; });
	}

	bool existsById(int id) const {
		return std::any_of(players.begin(), players.end(),
			[&](const Player& p) { return p.id == id; });
	}

	Player* getByName(const std::string& name) {
		auto it = std::find_if(players.begin(), players.end(),
			[&](const Player& p) { return p.name == name; });
		return (it != players.end()) ? &(*it) : nullptr;
	}

	Player* getById(int id) {
		auto it = std::find_if(players.begin(), players.end(),
			[&](const Player& p) { return p.id == id; });
		return (it != players.end()) ? &(*it) : nullptr;
	}
private:
	std::vector<Player> players;
	int nextPlayerId = 0;
};

class AttendanceManager {
public:
	AttendanceManager() = default;
	
	void ReadAttendanceData();
	void CalculateAttendancePoints(Player player, string attendanceDay);
	Player GetPlayer(string name);

	void CheckAttendance(string attendantName, string attendDay);
	bool IsNewPlayer(string name);
	void AddNewPlayer(string name);

private:
	enum class PointCategory {
		Weekdays = 0,    // 0
		Weekends = 1,    // 1
		TrainnigDay = 2, // 2

		PointCategoryCount = 3
	};

	static constexpr int MAX_PLAYER_COUNT = 100;
	map<string, int> inputData;

	PlayerRepo playerRepo;

	int attendanceCountPerDay[MAX_PLAYER_COUNT][static_cast<int>(PointCategory::PointCategoryCount)];
};
