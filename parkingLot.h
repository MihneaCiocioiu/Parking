#pragma once
#include <vector>
#include <iostream>
class parkingLot {
private:
	int capacity;
	int length;
	vector<int> a;
public:
	parkingLot() {
		capacity = 0;
		a.clear();
	}
	parkingLot(int size) {
		capacity = size;
		a.resize(capacity, 6);
	}
	int getSize() {
		return capacity;
	}
	void show() {
		for (int i = 0; i < a.size(); i++) {
			cout << a[i] << " ";
		}
	}
};

