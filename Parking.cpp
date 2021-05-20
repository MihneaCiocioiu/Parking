// Parking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include "parkingLot.h"
#include "car.h"

using namespace std;
parkingLot a,b,c;

int main() {
    a=parkingLot(30);
    b=parkingLot(50);
    c=parkingLot(45);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,  FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << a.getSize() << "\n";
    a.show({ 0,0 });
    int width = a.getWidth();
    b.show({ 30,0 });
    SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    c.show({ 0,15 });
  //  SetConsoleCursorPosition(hConsole, { 8,15 });
   // a.show({ 8,15 });
}