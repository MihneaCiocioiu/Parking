#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

class car {
private:
	int parkedTime;///*15 for minutes
	int ID;
	int lotRow;
	int lotCol;
	int parkedPlace;
	int arrivalTime;
	int timeUntilPay=0;
	int alarm = 0;
	int maxTime;
	const char* parkingLotID;
public:
	void showTime(int currentTime) {
		int hour = (currentTime / 60)%24;
		int minute = currentTime % 60;
		if (hour < 10) cout << 0 << hour;
		else cout << hour;
		cout << ":";
		if (minute < 10) cout << 0 << minute;
		else cout << minute;
		cout << " ";
		if (hour <= 12) cout << "AM";
		else  if (hour <= 23) cout << "PM";
	}
	void showTimeWithoutAm(int currentTime) {
		int hour = (currentTime / 60) % 24;
		int minute = currentTime % 60;
		if (hour < 10) cout << 0 << hour;
		else cout << hour;
		cout << ":";
		if (minute < 10) cout << 0 << minute;
		else cout << minute;
		cout << " ";
	}
	car() {
		parkedTime = 0;
	}
	car(int id) {
		ID = id;
	}
	car(int id, int _parkedTime) {
		ID = id;
		parkedTime = _parkedTime;
	}
	car(int id, int _parkedTime, int _lotRow, int _lotCol,int _parkedPlace,int _arrivalTime, const char* _parkingLotID, int _maxTime) {
		ID = id;
		parkedTime = _parkedTime;
		lotRow = _lotRow;
		lotCol = _lotCol;
		parkingLotID = _parkingLotID;
		parkedPlace = _parkedPlace;
		arrivalTime = _arrivalTime;
		maxTime = _maxTime;
	}
	void show(_COORD coord) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, coord);
		cout << "car: " << ID << " " << "Parked in: " << parkingLotID << " for: "; showTimeWithoutAm(parkedTime * 15); cout << "hours " << "Arrived at: "; showTime(arrivalTime);
		cout << " " << "Leaving at: "; showTime(arrivalTime + parkedTime * 15);
	}
	void checkAlarm(int currentTime) {
		if (abs((arrivalTime + (parkedTime * 15))-currentTime)  <= 10&&alarm==0) {
			alarm = 1;
			int extend = rand() % 4;
			if (extend==1) {
				arrivalTime = currentTime;
				parkedTime = rand() % maxTime;
				if (parkedTime == 0) parkedTime = 1;
				alarm = 0;
			}
		}
	}
	int getAlarm() {
		return alarm;
	}
	int getparkedLocation() {
		return parkedPlace;
	}
	int getParkedTime() {
		return parkedTime;
	}
	int getLeavingTime() {
		return arrivalTime + parkedTime * 15;
	}
	int pay(int currentTime) {
		if (timeUntilPay >= 15) {
			timeUntilPay = 0;

			return 1;
		}
		timeUntilPay++;
		return 0;
	}
	int getID() {
		return ID;
	}
	void setID(int id) {
		ID = id;
	}
	int getRow() {
		return lotRow;
	}
	int getCol() {
		return lotCol;
	}
};