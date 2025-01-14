/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
class DispatcherUnit{
    public:
    void getnextfloor(int currfloor,int destfloor){
        cout<<"Moving elevator from "<<currfloor<<"to floor"<<destfloor<<endl;
        
    }
};
class CallingUnit{
    shared_ptr<DispatcherUnit>dispatcherUnit;
    public:
    CallingUnit(shared_ptr<DispatcherUnit>dispatcherUnit):dispatcherUnit(move(dispatcherUnit)){}
    void moveelevator(int currfloor,int destfloor){
        dispatcherUnit->getnextfloor(currfloor,destfloor);
    }
};
Class ElevatorCar{
    bool ismoving;
    bool isgoingup;
    int currfloor;
    shared_ptr<CallingUnit>callingUnit;
    public:
    ElevatorCar(bool isgoingup,bool ismoving,int currfloor,shared_ptr<CallingUnit>callingUnit):isgoingup(isgoingup),ismoving(ismoving),currfloor(currfloor),callingUnit(callingUnit){}
    void gotofloor(int destfloor){
        callingUnit->moveelevator(currfloor,destfloor);
        currfloor=destfloor;
        cout<<"Elevator is now at floor"<<currfloor<<endl;
    }
};
class FloorCallingUnit{
    int currfloor;
    shared_ptr<callingUnit>callingUnit;
    public:
    FloorCallingUnit(int currfloor,shared_ptr<callingUnit>callingUnit):
    currfloor(currfloor),callingUnit(callingUnit)){}
    
    void callelevator(int destfloor){
        callingUnit->moveelevator(currfloor,destfloor);
    }

};