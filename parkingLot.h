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
	int length=6;
	int id;
	const char* type;
	vector<vector<car>> a;
public:
	parkingLot() {
		capacity = 0;
		a.clear();
	}
	parkingLot(int size, const char *Type) {
		capacity = size;
		type = Type;
		a.resize(length, vector<car>(capacity / length, 0));
		if (capacity % length != 0) {
			for (int i = 0; i < capacity % length; i++) {
				a[i].push_back(car(0));
			}
		}
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
	int getWidth() {
		if (capacity % length) return 2 + capacity / length * 4 + 4;
		else return  2 + capacity / length * 4;
	}
	void show(_COORD coord) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Id: " << capacity;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Type: " << type;
		coord.Y++;
		SetConsoleCursorPosition(hConsole, coord);
		cout << "Capacity: " << capacity;
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
				int id = a[i][j].getID();
				if (id == 0) cout << "   ";
				else if (id <= 9) cout << "  ";
				else if (id <= 99) cout << " ";
				else cout << id;
			}
			if (i < l && l != 0) {
				cout << (char)179;
				int id = a[i][L].getID();
				if (id==0) cout<<"   ";
				else if (id <= 9) cout << "  ";
				else if (id <= 99) cout << " ";
				else cout << id;
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

