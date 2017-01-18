//
// Created by gili on 18/01/17.
//

#include "Validation.h"

Validation::Validation(bool isServer) {
    this->is_server = isServer;
}

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
bool Validation::validTrip(Map* map, int id, int xStart, int yStart, int xEnd, int yEnd,
                           int numOfPassengers, double tarrif, int startTime) {
    if(this->is_server){
        bool valid = true;
        if (id < 0)
            valid = false;
        if (xStart < 0 || yStart < 0 || xEnd < 0 || yEnd < 0)
            valid = false;
        if (xStart >= map->getRowsSize() || xEnd >= map->getRowsSize()
            || yStart >= map->getColumnsSize() || yEnd >= map->getColumnsSize())
            valid = false;
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

bool Validation::validCab(int id, int type, CarType manufacture, Color color) {
    if(this->is_server){
        bool valid = true;
        if (id < 0)
            valid = false;
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

bool Validation::validDriverLength(int numOfArgument) {
    if (!this->is_server){
        if (numOfArgument != 5)
            return false;
        return true;
    }
    return false;
}

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