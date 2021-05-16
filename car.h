#pragma once
class car {
private:
	int parkedTime;
	int ID;
public:
	car() {
		parkedTime = 0;
	}
	car(int id) {
		ID = id;
	}
	int getParkedTime() {
		return parkedTime;
	}
	int getID() {
		return ID;
	}
	void setID(int id) {
		ID = id;
	}
};