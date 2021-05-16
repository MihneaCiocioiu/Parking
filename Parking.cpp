// Parking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include "parkingLot.h"
#include "car.h"

using namespace std;
parkingLot a;
car c;

int main() {
    a=parkingLot(27);
    c = car(100);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    cout << a.getSize()<<"\n";
    a.show();
    cout << c.getID();
}