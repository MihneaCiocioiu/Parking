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
int currentTime=1420;

int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0) lot[i][j] = parkingLot(30, "orange");
            if (i == 1) lot[i][j] = parkingLot(30, "blue");
            if (i == 2) lot[i][j] = parkingLot(30, "purple");
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //a = parkingLot(27,"orange");
    //a.parkCar(27);
    //a.show({ 0,0 });
    /*  SetConsoleTextAttribute(hConsole,  FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << a.getSize() << "\n";
    a.show({ 0,0 });
    int width = a.getWidth();
    b.show({ 30,0 });
    SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    c.show({ 0,18 }); */
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
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                else if (i == 1) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                else SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                lot[i][j].show({ (short)j * (short)(max(13,lot[i][j].getWidth())),(short)1+ (short)i * 16 });
            }
        }
     //   Sleep(1000);
        currentTime++;
        system("cls");
      //  cout.flush();
    }
  //  SetConsoleCursorPosition(hConsole, { 8,15 });
   // a.show({ 8,15 });
}