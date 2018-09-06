//
// Created by sean on 4/16/18.
//

#include "Plane.h"
using namespace std;
Plane::Plane(int absoluteTime, int numcargo, int numpassengers, int numchildren, int numgrandchildren, int numfuel){
    absoluteTimeAvailableForProcessing = absoluteTime;
    cargo = numcargo;
    passengers = numpassengers;
    children = numchildren;
    grandchildren = numgrandchildren;
    fuel = numfuel;
}

void Plane::refuel() {
    absoluteTimeAvailableForProcessing+=10;
    fuel+=30;
}

void Plane::update(int time){
    
    if(fuel>0){
        fuel--;
    }
    if(time==absoluteTimeAvailableForProcessing){
        requestAvailableForProcessing = true;
    }
    if(requestAvailableForProcessing) {
        waitTime = time - absoluteTimeAvailableForProcessing;
    }
    calculatePriority();
}

double Plane::calculateFuelFactor(int fuelAmount){
    double fuelFactor = 20/fuelAmount;
    return fuelFactor;
}

void Plane::calculatePriority() {
    
    if(!requestAvailableForProcessing)
        priority = -1;
    else {
        double fuelFactor = calculateFuelFactor(fuel);
        priority = children * CHILDREN_FACTOR + grandchildren * GRANDCHILDREN_FACTOR + cargo * CARGO_FACTOR +
        passengers * PASSENGER_FACTOR + fuelFactor * fuel;
    }
}

void Plane::setCrash(bool planeCrashed){crashed = planeCrashed;}
int Plane::getcargo(){return cargo;}
int Plane::getpassengers(){return passengers;}
int Plane::getchildren(){return children;}
int Plane::getgrandchildren(){return grandchildren;}
int Plane::getwaitTime(){return waitTime;}
int Plane::getpriority(){return priority;}
int Plane::getcrashed(){return crashed;}
bool Plane::getrequestAvailableForProcessing(){return requestAvailableForProcessing;}
char Plane::getTypeOfFlight() {return typeOfFlight;}
