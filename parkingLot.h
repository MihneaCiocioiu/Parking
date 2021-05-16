#pragma once
#include <vector>
#include <iostream>
#include "car.h"

using namespace std;

class parkingLot {
private:
	int capacity;
	int length=6;
	vector<vector<car>> a;
public:
	parkingLot() {
		capacity = 0;
		a.clear();
	}
	parkingLot(int size) {
		capacity = size;
		a.resize(capacity/length,vector<car>(length,0));
		if (capacity % length != 0) {
			a.push_back(vector<car>(capacity % length,0));
		}
		int id = 0;
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < a[i].size(); j++) {
				a[i][j].setID(++id);
			}
		}
	}
	int getSize() {
		return capacity;
	}
	void show() {
		for (auto line : a) {
			for (auto j : line) {
				cout << (char)179;
				//j.getID() << (char)179;
				int id = j.getID();
				if (id <= 9) cout << "  ";
				else if (id <= 99) cout << " ";
				cout << id;
			}
			cout << (char)179;
			cout << "\n";
			for (int i = 0; i < length; i++) {
				cout << (char)197<<(char)196 << (char)196 << (char)196;
			}
			cout<<(char)197;
			cout << "\n";
		}
	}
};

