#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include "car.h"
#include <cstring>

using namespace std;

class parkingLot {
private:
	int capacity;
	int length=5;
	int id;
	int profit=0;
	int normalPrice;
	int extraPrice;
	int extraPriceStart;
	int extraPriceEnd;
	int cost=1;
	int maxTime;
	char type[20];
	char location[20];
	char ID[10];
	vector<vector<car>> a;
public:
	parkingLot() {
		capacity = 0;
		a.clear();
	}
	parkingLot(int size, char Type[]) {
		capacity = size;
		strcpy_s(type , Type);
		a.resize(length, vector<car>(capacity / length, 0));
		if (capacity % length != 0) {
			for (int i = 0; i < capacity % length; i++) {
				a[i].push_back(car(0));
			}
		}
	}
	parkingLot(int size, char Type[20],char Location[20],int Id,int _normalPrice, int _extraPrice, int _extraPriceStart, int _extraPriceEnd) {
		capacity = size;
		normalPrice = _normalPrice;
		extraPrice = _extraPrice;
		extraPriceStart = _extraPriceStart;
		extraPriceEnd = _extraPriceEnd;
		strcpy_s(type , Type);
		strcpy_s(location , Location);
		id = Id;
		a.resize(length, vector<car>(capacity / length, 0));

		char name[10];
		if (strcmp(type, "orange") == 0) {
			maxTime = 4;
			strcpy_s(name, "O_");
		}

		else if (strcmp(type, "blue") == 0) {
			maxTime = 12;
			strcpy_s(name, "B_");
		}
		else if (strcmp(type, "purple") == 0) {
			maxTime = 96;
			strcpy_s(name, "P_");
		}
		if (id < 10) {
			strcat_s(name, "00");
			char aa[2];
			aa[1] = 0;
			aa[0] = '0' + id;
			strcat_s(name, aa);
		}
		else if (id < 100) {
			strcat_s(name, "0");
			char aa[3];
			aa[2] = 0;
			strcat_s(name, aa);
			int c1 = id / 10;
			int c2 = id % 10;
			aa[0] = '0' + c1;
			aa[1] = '0' + c2;
			strcat_s(name, aa);
		}
		strcpy_s(ID , name);
		if (capacity % length != 0) {
			for (int i = 0; i < capacity % length; i++) {
				a[i].push_back(car(0));
			}
		}
	}
	const char* getStringID() {
		return ID;
	}
	parkingLot(int size) {
		capacity = size;
		a.resize(length,vector<car>(capacity/length,0));
		if (capacity % length != 0) {
			for (int i = 0; i < capacity % length; i++) {
				a[i].push_back(car(0));
			}
		}
		int id = 0;
		int i, j;
		for (j = 0; j < capacity/length; j++) {
			for (i = 0; i < a.size(); i++) {
				a[i][j].setID(++id);
			}
		}
		if (capacity % length != 0) {
			for (i = 0; i < capacity % length; i++) {
				a[i][capacity / length].setID(++id);
			}
		}
	}
	int getSize() {
		return capacity;
	}
	int getMaxTime() {
		return maxTime;
	}
	int getWidth() {
		if (capacity % length) return max(27,2 + capacity / length * 4 + 4);
		else return  max(27, 2 + capacity / length * 4);
	}
	int isEmpty(int location) { 
		if (a[(location-1) % length ][(location-1) / length].getID() != 0) return 0;
		return 1;
	}
	void parkCar(int location, car Car) {
		a[(location-1) % length][(location-1) / length]=Car;
	}
	void calculateProfit() {
		for (auto line : a) {
			for (auto car : line) {
				if (car.getID()) profit +=cost;
			}
		}
	}
	int getProfit() {
		return profit;
	}
	void cash(int value) {
		profit += value;
	}
	int getCurrentPrice(int currentTime) {
		int hour = (currentTime / 60) % 24;
		if (hour >= extraPriceStart && hour <= extraPriceEnd) {
			cost = extraPrice;
		}
		else cost = normalPrice;
		return cost;
	}
	void checkAlarmLocation(int location, int currentTime) {
		a[(location - 1) % length][(location - 1) / length].checkAlarm(currentTime);
	}
	void show(_COORD coord) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Id: " << ID;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Location: " << location;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Profit: " << profit;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Type: " << type;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Capacity: " << capacity;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Normal price: " << normalPrice;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Extra price: " << extraPrice;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Extra price hours: " << extraPriceStart<<" - "<<extraPriceEnd;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << (char)218;
		int L = capacity / length;
		int l = capacity % length;
		for (int j = 0; j < L-1; j++) {
			cout << (char)196 << (char)196 << (char)196 << (char)194;
		}
		if (l!=0) cout << (char)196 << (char)196 << (char)196 << (char)194;
		cout << (char)196 << (char)196 << (char)196 << (char)191;
		coord.Y++;
		for (int i = 0; i < a.size(); i++) {
			SetConsoleCursorPosition(hConsole, coord);
			for (int j = 0; j < L; j++) {
				cout << (char)179;
				if (a[i][j].getAlarm() == 0) {
					int id = a[i][j].getID();
					if (id == 0) cout << "   ";
					else {
						if (id <= 9) cout << "  ";
						else if (id <= 99) cout << " ";
						cout << id;
					}
				}
				else {
					int id = a[i][j].getID();
					if (id <= 9) cout << "! ";
					else if (id <= 99) cout << "!";
					cout << id;
				}
			}
			if (i < l && l != 0) {
				cout << (char)179;
				if (!a[i][L].getID()) {
					int id = a[i][L].getID();
					if (id == 0) cout << "   ";
					else {
						if (id <= 9) cout << "  ";
						else if (id <= 99) cout << " ";
						cout << id;
					}
				}
				else {
					int id = a[i][L].getID();
					if (id <= 9) cout << "! ";
					else if (id <= 99) cout << "!";
					cout << id;
				}
			}
			cout << (char)179;
			coord.Y++;
			SetConsoleCursorPosition(hConsole, coord);
			if (i != a.size()-1) {
				cout << (char)195;
				for (int j = 0; j < L - 1; j++) {
					cout << (char)196 << (char)196 << (char)196 << (char)197;
				}
				if (l != 0 && i < l) {
					cout << (char)196 << (char)196 << (char)196 << (char)197;
				}
				cout << (char)196 << (char)196 << (char)196;
				if (i == l - 1 && l) cout << (char)217;
				else cout << (char)180;
				coord.Y++;
			}
			else {
				cout << (char)192;
				for (int j = 0; j < L - 1; j++) {
					cout << (char)196 << (char)196 << (char)196 << (char)193;
				}
				if (l != 0 && i < l) {
					cout << (char)196 << (char)196 << (char)196 << (char)193;
				}
				cout << (char)196 << (char)196 << (char)196 << (char)217;
			}
		}
	}
};

