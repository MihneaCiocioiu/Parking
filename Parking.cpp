// Parking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "parkingLot.h"
#include "car.h"

using namespace std;
parkingLot a,b,c;
parkingLot lot[4][4];

int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0) lot[i][j] = parkingLot(30, "orange");
            if (i == 1) lot[i][j] = parkingLot(30, "blue");
            if (i == 2) lot[i][j] = parkingLot(30, "purple");
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    /*  SetConsoleTextAttribute(hConsole,  FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << a.getSize() << "\n";
    a.show({ 0,0 });
    int width = a.getWidth();
    b.show({ 30,0 });
    SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    c.show({ 0,18 }); */
    int row = rand() % 3;
    int col = rand() % 3;
    int place = rand() % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i==0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            else if (i==1) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            else SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            lot[i][j].show({(short)j* (short) (max(13,lot[i][j].getWidth())),(short)i * 16 });
        }
    }
  //  SetConsoleCursorPosition(hConsole, { 8,15 });
   // a.show({ 8,15 });
}