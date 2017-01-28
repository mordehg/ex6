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

    bool validObst(Map* map, int numOfArgument, vector<string> obstData);

    bool validTripLength(int numOfArgument);

    bool validTrip(Map* map, vector<string> trip_data);

    bool validCabLength(int numOfArgument);

    bool validCab(vector<string> cab_data);

    bool validDriverId(vector<string> driverId_data);

    bool validDriverIdLength(int numOfArgument);

    bool validDriverLength(int numOfArgument);

    bool validDreiver(vector<string> driverData);

    bool validObsLength(int numOfArgument);

    bool validObsPoint(Map* map, vector<string> pointData);

    bool validPointLength(int numOfArgument);

    bool validChoiceLength(int numOfArgument);

    bool validNumDriverLength(int numOfArgument);

    bool validNumDrivers(vector<string> driverNumData);

    bool isNumber(string str);
};


#endif //EX5_VALIDATION_H
