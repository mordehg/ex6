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
bool Validation::validMap(int size_x, int size_y) {
    if (this->is_server) {
        if (size_x <= 0 || size_y <= 0) {
            cout << "-1" << endl;
            return false;
        }
        return true;
    }
    return false;
}

/**
 * cheack if obsticales input are valid. if not print -1.
 * @param map of the city
 * @param obsticalNum num of obsticales.
 * @return true if valid, else false;
 */
bool Validation::validObst(Map* map,int obsticalNum) {
    if (this->is_server) {
        if (obsticalNum < 0 || obsticalNum > map->mapSize()) {
            cout << "-1" << endl;
            return false;
        }
        return true;
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
bool Validation::validTrip(Map* map, int id, int xStart, int yStart, int xEnd, int yEnd,
                           int numOfPassengers, double tarrif, int startTime) {
    if(this->is_server){
        bool valid = true;
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
        if (map->getBlock(xStart,xEnd)->getIsObstacle()){
            valid=false;
        }
        if (map->getBlock(yStart,yEnd)->getIsObstacle()){
            valid=false;
        }
        if (numOfPassengers <= 0)
            valid = false;
        if (tarrif < 0)
            valid = false;
        if (startTime < 0)
            valid = false;

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
bool Validation::validCab(int id, int type, CarType manufacture, Color color) {
    if(this->is_server){
        bool valid = true;
        if (id < 0)
            valid = false;
        if (this->taxiCenter->getCab(id)){
            valid=false;
        }
        if (type != 1 && type != 2)
            valid = false;
        if ((char)manufacture != 'H' && (char)manufacture != 'S'
            && (char)manufacture != 'T' && (char)manufacture != 'F')
            valid = false;
        if ((char)color != 'R' && (char)color != 'B' &&
                (char)color != 'G' && (char)color != 'P'
                && (char)color != 'W')
            valid = false;
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
bool Validation::validDriverId(int id){
    if(this->is_server){
        if (!this->taxiCenter->getDriver(id)){
            cout << "-1" << endl;
            return false;
        }
        return true;
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
bool Validation::validDreiver(int id, int age, Status status, int exp, int cabID) {
    if (!this->is_server) {
        bool valid = true;
        if (id < 0)
            valid = false;
        if (age <= 0)
            valid  = false;
        if ((char)status != 'S' && (char)status != 'M'
            && (char)status != 'D' && (char)status != 'W')
            valid = false;
        if (exp < 0)
            valid = false;
        if (cabID < 0)
            valid = false;
        return valid;
    }
    return false;
}

