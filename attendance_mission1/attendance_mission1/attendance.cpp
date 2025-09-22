#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
	string w;
	string wk;
};

map<string, int> id1;
int id_cnt = 0;

//dat[�����ID][����]
int dat[100][100];
int points[100];
int grade[100];
string names[100];

int wed[100];
int weeken[100];

void input2(string w, string wk) {
	//ID �ο�
	if (id1.count(w) == 0) {
		id1.insert({ w, ++id_cnt });

		if (w == "Daisy") {
			int debug = 1;
		}

		names[id_cnt] = w;
	}
	int id2 = id1[w];

	//������
	if (w == "Daisy") {
		int debug = 1;
	}


	int add_point = 0;
	int index = 0;
	if (wk == "monday") {
		index = 0;
		add_point++;
	}
	if (wk == "tuesday") {
		index = 1;
		add_point++;
	}
	if (wk == "wednesday") {
		index = 2;
		add_point += 3;
		wed[id2] += 1;
	}
	if (wk == "thursday") {
		index = 3;
		add_point++;
	}
	if (wk == "friday") {
		index = 4;
		add_point++;
	}
	if (wk == "saturday") {
		index = 5;
		add_point += 2;
		weeken[id2] += 1;
	}
	if (wk == "sunday") {
		index = 6;
		add_point += 2;
		weeken[id2] += 1;
	}

	//�����ID�� ���� �����Ϳ� 1�� ����
	dat[id2][index] += 1;
	points[id2] += add_point;
}

bool IsRemovedPlayer(int playerId) {
	return (grade[playerId] != 1 && grade[playerId] != 2 && wed[playerId] == 0 && weeken[playerId] == 0);
}

void PrintRemovedPlayer() {
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int PlayerID = 1; PlayerID <= id_cnt; PlayerID++) {
		if (IsRemovedPlayer(PlayerID) == true) {
			std::cout << names[PlayerID] << "\n";
		}
	}
}

void ReadAttendanceData()
{
	ifstream fin{ "attendance_weekday_500.txt" }; //500�� ������ �Է�
	for (int i = 0; i < 500; i++) {
		string t1, t2;
		fin >> t1 >> t2;
		input2(t1, t2);
	}
}

void CalculateAttendancePoint() {
	for (int i = 1; i <= id_cnt; i++) {
		if (dat[i][2] > 9) {
			points[i] += 10;
		}

		if (dat[i][5] + dat[i][6] > 9) {
			points[i] += 10;
		}

		if (points[i] >= 50) {
			grade[i] = 1;
		}
		else if (points[i] >= 30) {
			grade[i] = 2;
		}
		else {
			grade[i] = 0;
		}
	}
}

void GradeAttendant() {
	for (int i = 1; i <= id_cnt; i++) {
		cout << "NAME : " << names[i] << ", ";
		cout << "POINT : " << points[i] << ", ";
		cout << "GRADE : ";

		if (grade[i] == 1) {
			cout << "GOLD" << "\n";
		}
		else if (grade[i] == 2) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}
}

int main() {
	ReadAttendanceData();
	CalculateAttendancePoint();
	GradeAttendant();
	PrintRemovedPlayer();
}