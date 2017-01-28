//
// Created by gili on 18/01/17.
//

#include "Validation.h"

/**
 * constractur.
 * @param isServer if is server true, client false
 * @param taxiCenter from server. if celient contain null.
 * @return
 */
Validation::Validation(bool isServer) {
    this->is_server = isServer;
    this->taxiCenter=NULL;

}

void Validation::setTaxiCenter(TaxiCenter* taxiCenter){
    if(this->is_server)
        this->taxiCenter=taxiCenter;
}

/**
 * distractur.
 */
Validation::~Validation(){}

bool Validation::validMapNum(int numOfArgument) {
    if (this->is_server) {
        if (numOfArgument != 2) {
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}


/**
 * check if the input of map is valid. if not print -1.
 * @param size_x x input
 * @param size_y y input
 * @return true if valid, else false;
 */
bool Validation::validMap(vector<string> mapData) {
    int size_x,size_y;
    if (this->is_server) {
        bool valid=true;
        if(mapData.size()!=2){
            valid=false;
        }
        else{
            if(!this->isNumber(mapData[0])||!this->isNumber(mapData[1])){
                valid=false;
            }
            size_x=atoi(mapData[0].c_str());
            size_y=atoi(mapData[1].c_str());
            if (size_x <= 0 || size_y <= 0) {
                valid=false;
            }
        }
        if(!valid){
            cout << "-1" << endl;
        }
        return valid;
    }
    return false;
}

/**
 * cheack if obsticales input are valid. if not print -1.
 * @param map of the city
 * @param obsticalNum num of obsticales.
 * @return true if valid, else false;
 */
bool Validation::validObst(Map* map,int numOfArgument, vector<string> obsData) {
    if (this->is_server) {
        if (validObsLength(numOfArgument)) {
            bool valid=true;
            if (!this->isNumber(obsData[0])){
                valid=false;
            }
            else{
                int obsticalNum=atoi(obsData[0].c_str());
                if (obsticalNum < 0 || obsticalNum > map->mapSize()) {
                    valid=false;
                }
            }
            if (!valid) {
                cout << "-1" << endl;
            }
            return valid;
        }
    }
    return false;
}

/**
 * check if num of arguments of trip is valid. if not print -1.
 * @param numOfArgument num of arguments in trip.
 * @return true if valid, else false;
 */
bool Validation::validTripLength(int numOfArgument) {
    if (this->is_server) {
        if (numOfArgument != 8) {
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

/**
 * check if arguments of trip are valid. if not print -1.
 * @param map of the city
 * @param id of trip
 * @param xStart x value of start point
 * @param yStart y value of start point
 * @param xEnd x value of end point
 * @param yEnd y value of end point
 * @param numOfPassengers number of passengers
 * @param tarrif tarrif
 * @param startTime start time of trip
 * @return true if valid, else false;
 */
bool Validation::validTrip(Map* map, vector<string> trip_data) {
    int id, xStart, yStart, xEnd, yEnd, numOfPassengers, startTime;
    double tariff;
    if(this->is_server){
        bool valid = true;
        if(!this->isNumber(trip_data[0])
                ||!this->isNumber(trip_data[1])
                || !this->isNumber(trip_data[2])
                || !this->isNumber(trip_data[3])
                || !this->isNumber(trip_data[4])
                || !this->isNumber(trip_data[5])
                || !this->isNumber(trip_data[6])
                || !this->isNumber(trip_data[7])){
            valid=false;
        }
        else{
            id = atoi(trip_data[0].c_str());
            xStart = atoi(trip_data[1].c_str());
            yStart = atoi(trip_data[2].c_str());
            xEnd = atoi(trip_data[3].c_str());
            yEnd = atoi(trip_data[4].c_str());
            numOfPassengers = atoi(trip_data[5].c_str());
            tariff = (double) atoi(trip_data[6].c_str());
            startTime = atoi(trip_data[7].c_str());
            if (id < 0)
                valid = false;
            if(this->taxiCenter->getTrip(id)){
                valid=false;
            }
            if (xStart < 0 || yStart < 0 || xEnd < 0 || yEnd < 0)
                valid = false;
            if (xStart >= map->getRowsSize() || xEnd >= map->getRowsSize()
                || yStart >= map->getColumnsSize() || yEnd >= map->getColumnsSize())
                valid = false;
            else{
                if (map->getBlock(xStart,yStart)->getIsObstacle()){
                    valid=false;
                }
                if (map->getBlock(xEnd,yEnd)->getIsObstacle()){
                    valid=false;
                }
            }
            if(xStart==xEnd && yStart==yEnd){
                valid=false;
            }
            if (numOfPassengers <= 0)
                valid = false;
            if (tariff < 0)
                valid = false;
            if (startTime < 0)
                valid = false;
        }
        if (valid == false) {
            cout << "-1" << endl;
        }
        return valid;
    }
    return false;
}

/**
 * check if num of arguments of cab is valid. if not print -1.
 * @param numOfArgument num of arguments of cab
 * @return true if valid, else false;
 */
bool Validation::validCabLength(int numOfArgument) {
    if (this->is_server) {
        if (numOfArgument != 4) {
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

/**
 * check if arguments of cab are valid. if not print -1.
 * @param id cab id
 * @param type cab type
 * @param manufacture cab manufacture
 * @param color cab color
 * @return true if valid, else false;
 */
bool Validation::validCab(vector<string> cab_data) {
    int id, taxiType;
    char manufacturerLetter, colorLetter;
    if(this->is_server){
        bool valid = true;
        if(!this->isNumber(cab_data[0])||
                !this->isNumber(cab_data[1])){
            valid=false;
        }
        else{
            id = atoi(cab_data[0].c_str());
            taxiType = atoi(cab_data[1].c_str());
            manufacturerLetter = cab_data[2].c_str()[0];
            colorLetter = cab_data[3].c_str()[0];

            if (id < 0)
                valid = false;
            if (this->taxiCenter->getCab(id)){
                valid=false;
            }
            if (taxiType != 1 && taxiType != 2)
                valid = false;
            if (manufacturerLetter != 'H' && manufacturerLetter != 'S'
                && manufacturerLetter != 'T' && manufacturerLetter != 'F')
                valid = false;
            if (colorLetter != 'R' && colorLetter != 'B' &&
                colorLetter != 'G' && colorLetter != 'P'
                && colorLetter != 'W')
                valid = false;
        }
        if (valid == false) {
            cout << "-1" << endl;
        }
        return valid;
    }
    return false;
}

/**
 * cheack if num of arguments of driver id is valid. if not print -1.
 * @param numOfArgument of driver
 * @return true if valid, else false;
 */
bool Validation::validDriverIdLength(int numOfArgument){
    if(this->is_server){
        if(numOfArgument!=1){
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

/**
 * cheack if driver id not exist in system. if yes print -1.
 * @param id of driver
 * @return true if valid, else false;
 */
bool Validation::validDriverId(vector<string> driverId_data){
    if(this->is_server){
        bool valid=true;
        if(!this->isNumber(driverId_data[0])){
            valid=false;
        }
        else{
            int id=atoi(driverId_data[0].c_str());
            if (!this->taxiCenter->getDriver(id)){
                valid=false;
            }
        }
        if (!valid){
            cout << "-1" << endl;
        }
        return valid;
    }
    return false;
}

/**
 * cheack if num of arguments of driver is valid.
 * @param numOfArgument num of arguments of driver
 * @return true if valid, else false;
 */
bool Validation::validDriverLength(int numOfArgument) {
    if (!this->is_server){
        if (numOfArgument != 5)
            return false;
        return true;
    }
    return false;
}

/**
 * cheack if arguments of driver are valid.
 * @param id driver id
 * @param age driver age
 * @param status driver status
 * @param exp driver expirence
 * @param cabID cab id of driver
 * @return true if valid, else false;
 */
bool Validation::validDreiver(vector<string> driver_data) {
    int id,age,exp,cabID;
    char status;
    if (!this->is_server) {
        bool valid = true;
        if(!this->isNumber(driver_data[0]) ||
                !this->isNumber(driver_data[1]) ||
                !this->isNumber(driver_data[3]) ||
                !this->isNumber(driver_data[4])){
            return false;
        }
        id = atoi(driver_data[0].c_str());
        age = atoi(driver_data[1].c_str());
        status = driver_data[2].c_str()[0];
        exp = atoi(driver_data[3].c_str());
        cabID = atoi(driver_data[4].c_str());
        if (id < 0)
            valid = false;
        if (age <= 0)
            valid  = false;
        if (status != 'S' && status != 'M'
            && status != 'D' && status != 'W')
            valid = false;
        if (exp < 0)
            valid = false;
        if (cabID < 0)
            valid = false;
        return valid;
    }
    return false;
}

bool Validation::validObsLength(int numOfArgument) {
    if(this->is_server){
        if (numOfArgument != 1){
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

bool Validation::validObsPoint(Map* map, vector<string> pointData) {
    bool valid = true;
    if(this->is_server){
        if (!this->isNumber(pointData[0]) ||
                !this->isNumber(pointData[1])){
            valid=false;
        }
        else {
            int x = atoi(pointData[0].c_str());
            int y = atoi(pointData[1].c_str());
            if (x < 0 || y < 0)
                valid = false;
            if (x >= map->getRowsSize() || y >= map->getColumnsSize())
                valid = false;
            else if (map->getBlock(x,y)->getIsObstacle())
                valid = false;
        }
        if (!valid)
            cout << "-1" << endl;
    }
    return valid;
}

bool Validation::validPointLength(int numOfArgument) {
    if(this->is_server){
        if (numOfArgument != 2){
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

bool Validation::validChoiceLength(int numOfArgument) {
    if(this->is_server){
        if (numOfArgument != 1){
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

bool Validation::validNumDriverLength(int numOfArgument) {
    if(this->is_server){
        if (numOfArgument != 1){
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

bool Validation::validNumDrivers(vector<string> driverNumData){
    bool valid=true;
    if(this->is_server){
        if(!this->isNumber(driverNumData[0])){
            valid=false;
        }
        else{
            int num=atoi(driverNumData[0].c_str());
            if (num <= 0 ){
                valid=false;
            }
        }
        if(!valid){
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

bool Validation::isNumber(string str){
    for(int i=0; i<str.length(); i++){
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}