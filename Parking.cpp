// Parking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "parkingLot.h"
#include "car.h"

using namespace std;
vector<vector<parkingLot> > lot;
int currentTime=0;

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

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    ifstream fin("ParkingLots.txt");

    lot.resize(3);

    for (int k = 0; k < 3; k++) {
        char a[110];
        int n;
        fin.getline(a, 110);
        n = strlen(a);
        int nr = 0;
        for (int i = 0; i < n; i++) {
            if (isdigit(a[i])) {
                nr = nr * 10 +  a[i]-'0';
            }
        }
        int ID = 0;
        while (nr--) {
            int size = 0;
            fin.getline(a, 110);
            fin.getline(a, 110);
            for (int i = 0; a[i]; i++) {
                if (isdigit(a[i])) {
                    size = size * 10 + a[i]-'0';
                }
            }
            fin.getline(a, 110);
            int i = 0;
            while (a[i] != ':') {
                i++;
            }
            i += 2;
            char type[20];
            strcpy_s(type , a + i);
            char b[110];
            fin.getline(b, 110);
            i = 0;
            while (b[i] != ':') {
                i++;
            }
            i += 2;
            char location[20];
            strcpy_s(location , b + i);
            fin.getline(a, 110);
            i = 0;
            while (a[i] != ':') {
                i++;
            }
            i += 2;
            int normalPrice = 0;
            while (isdigit(a[i])) {
                normalPrice = normalPrice * 10 + a[i] - '0';
                i++;
            }
            fin.getline(a, 110);
            i = 0;
            while (a[i] != ':') {
                i++;
            }
            i += 2;
            int extraPrice, extraPriceStart, extraPriceEnd;
            if (isdigit(a[i])) {
                extraPrice = 0;
                extraPriceStart = 0;
                extraPriceEnd = 0;
                while (isdigit(a[i])) {
                    extraPrice = extraPrice * 10 + a[i] - '0';
                    i++;
                }
                fin.getline(a, 110);
                i = 0;
                while (a[i] != ':') {
                    i++;
                }
                i += 2;
                while (isdigit(a[i])) {
                    extraPriceStart = extraPriceStart * 10 + a[i] - '0';
                    i++;
                }
                fin.getline(a, 110);
                i = 0;
                while (a[i] != ':') {
                    i++;
                }
                i += 2;
                while (isdigit(a[i])) {
                    extraPriceEnd = extraPriceEnd * 10 + a[i] - '0';
                    i++;
                }
            }
            else {
                extraPrice = normalPrice;
                extraPriceStart = 0;
                extraPriceEnd = 0;
            }
            lot[k].push_back(parkingLot(size, type, location, ++ID,normalPrice,extraPrice,extraPriceStart,extraPriceEnd));
        }
    }

    vector<car> cars;

    srand(time(0));
    int ID = 1;

    int maxWidth = 0;

    for (int i = 0; i < lot.size(); i++) {
        int width = 0;
        for (int j = 0; j < lot[i].size(); j++) {
            width += max(27, lot[i][j].getWidth());
        }
        maxWidth = max(maxWidth, width);
    }

    maxWidth += 3;

    while (true) {
        cout << "Time: ";
        //currentTime / 60 << ':' << currentTime % 60 << "\n";
        showTime(currentTime);
        int spawn = rand() % 2;
        if (spawn) {
            int row = rand() % 3;
            int col = rand() % lot[row].size();
            int maxTime = lot[row][col].getMaxTime();
            int parkedTime = rand() % (maxTime);
            if (parkedTime == 0) parkedTime = 1;
            const char* name = lot[row][col].getStringID();
            int place = rand() % lot[row][col].getSize();
            place++;
            cars.push_back(car(ID++,parkedTime,row,col,place,currentTime,name,maxTime));
            if (lot[row][col].isEmpty(place)) lot[row][col].parkCar(place,cars[cars.size()-1]);
        }

        for (int i = 0; i < cars.size();i++) {
            if (cars[i].pay(currentTime)) {
                lot[cars[i].getRow()][cars[i].getCol()].cash(lot[cars[i].getRow()][cars[i].getCol()].getCurrentPrice(currentTime));
            }
        }

        for (int i = 0; i < cars.size(); i++) {
            lot[cars[i].getRow()][cars[i].getCol()].checkAlarmLocation(cars[i].getparkedLocation(),currentTime);

            if (currentTime==cars[i].getLeavingTime()) {
                lot[cars[i].getRow()][cars[i].getCol()].parkCar(cars[i].getparkedLocation(), car(0));
                cars.erase(cars.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < 3; i++) {
            int width = 0;
            for (int j = 0; j < lot[i].size(); j++) {
                if (i == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                else if (i == 1) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                else SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                lot[i][j].show({(short)width,(short)1 + (short)i * 19 });
                width += lot[i][j].getWidth();
            }
        }

        SetConsoleCursorPosition(hConsole, {(short)maxWidth,0});


        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

        cout << "CARS:\n";
        for (int i = 0; i < cars.size(); i++) {
            cars[i].show({ (short)maxWidth,(short)1 + (short)i });
        }
        Sleep(1000);
     //   system("pause");
        currentTime++;
        system("cls");
      //  cout.flush();
    }
}