//
// Created by gili on 18/01/17.
//

#ifndef EX5_VALIDATION_H
#define EX5_VALIDATION_H

#include <iostream>
#include "Map.h"
#include "Color.h"
#include "CarType.h"
#include "Status.h"
#include "TaxiCenter.h"

using namespace std;
class Validation {
private:
    bool is_server;
    TaxiCenter* taxiCenter;
public:
    Validation(bool isServer);

    void setTaxiCenter(TaxiCenter* taxiCenter);

    ~Validation();

    bool validMapNum(int numOfArgument);

    bool validMap(vector<string> mapData);

    bool validObst(Map* map, int obsticalNum);

    bool validTripLength(int numOfArgument);

    bool validTrip(Map* map, int id, int xStart, int yStart, int xEnd, int yEnd,
                   int numOfPassengers,double tarrif, int startTime);

    bool validCabLength(int numOfArgument);

    bool validCab(int id, int type, CarType manufacture, Color color);

    bool validDriverId(int id);

    bool validDriverIdLength(int numOfArgument);

    bool validDriverLength(int numOfArgument);

    bool validDreiver(vector<string> driverData);

    bool validObsLength(int numOfArgument);

    bool validObsPoint(Map* map, int x, int y);

    bool validPointLength(int numOfArgument);

    bool validChoiceLength(int numOfArgument);

    bool validNumDriverLength(int numOfArgument);

    bool validNumDrivers(int num);
};


#endif //EX5_VALIDATION_H
