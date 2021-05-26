// Parking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "parkingLot.h"
#include "car.h"
//#include <json/value.h>
//#include <jsoncpp/json/json.h>

using namespace std;
parkingLot a,b,c;
parkingLot lot[4][4];
int currentTime=0;

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    //ifstream jsonIn("parkingLots.json");
    //jsonIn >> parkingLots;
    lot[0][0] = parkingLot(30, "orange", "center");
    lot[0][1] = parkingLot(30, "orange", "busy area");
    lot[0][2] = parkingLot(30, "orange", "residential area");

    lot[1][0] = parkingLot(30, "blue", "center");
    lot[1][1] = parkingLot(30, "blue", "busy area");
    lot[1][2] = parkingLot(30, "blue", "residential area");

    lot[2][0] = parkingLot(30, "purple", "center");
    lot[2][1] = parkingLot(30, "purple", "busy area");
    lot[2][2] = parkingLot(30, "purple", "residential area");

    srand(time(0));
    while (true) {
        cout << "Time: ";
        //currentTime / 60 << ':' << currentTime % 60 << "\n";
        int hour = currentTime / 60;
        int minute = currentTime % 60;
        if (hour < 10) cout << 0 << hour;
        else cout << hour;
        cout << ":";
        if (minute < 10) cout << 0 << minute;
        else cout << minute;
        cout << " ";
        if (hour <= 12) cout << "AM";
        else  if (hour <= 23) cout << "PM";
        else currentTime = 0;
        int spawn = rand() % 2;
        if (spawn) {
            int row = rand() % 3;
            int col = rand() % 3;
            int place = rand() % lot[row][col].getSize();
            place++;
            if (lot[row][col].isEmpty(place)) lot[row][col].parkCar(place);
        }
        if (currentTime % 15 == 0) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    lot[i][j].calculateProfit();
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                else if (i == 1) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                else SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                lot[i][j].show({ (short)j * (short)(max(13,lot[i][j].getWidth())),(short)1+ (short)i * 18});
            }
        }
        Sleep(1000);
        currentTime++;
        system("cls");
      //  cout.flush();
    }
}