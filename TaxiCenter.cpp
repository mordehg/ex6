//
// Created by moran on 03/12/16.
//

#include "TaxiCenter.h"

using namespace std;

/**
 * constructor TaxiCenter doesn't get any argument, the vectors are
 * initialize in the .h file
 */
TaxiCenter::TaxiCenter(Bfs* bfs1) {
    bfs=bfs1;
}

/**
 * destructor.
 */
TaxiCenter::~TaxiCenter() {
    while (!trips.empty()) {
        Trip *t = trips.back();  // get the trip
        trips.pop_back();        // take out the trip from the vector
        delete (t);              // delete the trip
    }

    while (!driversInfo.empty()) {
        Driver *d = driversInfo.back();
        driversInfo.pop_back();
        delete (d);
    }

    while (!cabs.empty()) {
        Cab *c = cabs.back();
        cabs.pop_back();
        delete (c);
    }
}

/**
 * set vector of driversinfo
 * @param driversInfo the vector to set
 */
void TaxiCenter::setDriversInfo(const vector<Driver *> &driversInfo) {
    TaxiCenter::driversInfo = driversInfo;
}

/**
 * set cabs vector.
 * @param cabs the vector to set
 */
void TaxiCenter::setCabs(const vector<Cab *> &cabs) {
    TaxiCenter::cabs = cabs;
}

/**
 * set trips vector.
 * @param trips the vector to set
 */
void TaxiCenter::setTrips(const vector<Trip *> &trips) {
    TaxiCenter::trips = trips;
}

/**
 * access.
 * @return the driversInfo vector
 */
const vector<Driver *> &TaxiCenter::getDriversInfo() const {
    return driversInfo;
}

/**
 * access.
 * @return the cabs vector
 */
const vector<Cab *> &TaxiCenter::getCabs() const {
    return cabs;
}

/**
 * access.
 * @return the trips vector
 */
const vector<Trip *> &TaxiCenter::getTrips() const {
    return trips;
}

/**
 * add one driver to driversInfo vector, each driver get connected to his cab
 * @param driver the new driver
 */
void TaxiCenter::addDriverInfo(Driver *driver) {
    driversInfo.push_back(driver);
    if (!cabs.empty()) {
        for (vector<Cab *>::iterator itCabs = cabs.begin();
             itCabs != cabs.end(); itCabs++) {
            if ((*itCabs)->getCabId() == driver->getCabId()) {
                driver->setCab((*itCabs));
            }
        }
    }
}

/**
 * add one cab to cabs vector
 * @param cab the new cab
 */
void TaxiCenter::addCab(Cab *cab) {
    cabs.push_back(cab);

}

/**
 * add one trip to trips vectoe
 * @param trip the new trip
 */
void TaxiCenter::addTrip(Trip *trip) {
    trips.push_back(trip);

}

/**
 * get the number of the drivers
 * @return the num of drivers
 */
long TaxiCenter::numOfDrivers() {
    return driversInfo.size();
}

/**
 * get the number of the cabs
 * @return the num of cabs
 */
long TaxiCenter::numOfCab() {
    return cabs.size();
}

/**
 * get the number of the trips
 * @return the num of trips
 */
long TaxiCenter::numOfTrips() {
    return trips.size();
}

/**
* delete trip at index i from trips vector
 */
void TaxiCenter::popTrip(int i) {
    vector<Trip *> temp;
    int j=0;
    while (!trips.empty()) {
        if(j==i){
            Trip *t = trips.back();
            trips.pop_back();
            delete (t);
        }
        else{
            temp.push_back(trips.back());
            trips.pop_back();
        }
        j++;
    }
    while (!temp.empty()) {
        trips.push_back((temp.back()));
        temp.pop_back();
    }
}

/**
 * delete driver at index i from drivers vector.
 */

void TaxiCenter::popDriver(int i) {
    vector<Driver *> temp;
    int j=0;
    while (!driversInfo.empty()) {
        if (j==i){
            Driver *d = driversInfo.back();
            driversInfo.pop_back();
            delete (d);
        }
        else{
            temp.push_back(driversInfo.back());
            driversInfo.pop_back();
        }
        j++;
    }
    while (!temp.empty()) {
        driversInfo.push_back((temp.back()));
        temp.pop_back();
    }
}

/**
 * delete cab at index i from cabs vector.
 */

void TaxiCenter::popCab(int i) {
    vector<Cab *> temp;
    int j=0;
    while (!cabs.empty()) {
        if(i==j){
            Cab *c = cabs.back();
            cabs.pop_back();
            delete (c);
        }
        else{
            temp.push_back(cabs.back());
            cabs.pop_back();
        }
        j++;
    }
    while (!temp.empty()) {
        cabs.push_back((temp.back()));
        temp.pop_back();
    }
}

/**
 * get the driver
 * @return the driver with the given id, if not have return null;
 */
Driver *TaxiCenter::getDriver(int id) {
    for (int i=0; i< driversInfo.size();i++)
    {
        if(driversInfo[i]->getDriverId()==id){
            return driversInfo[i];
        }
    }
    return NULL;
}

/**
 * get the cab
 * @return the cab with the given id, if not have return null;
 */
Cab *TaxiCenter::getCab(int id) {
    for (int i=0;i<cabs.size();i++){
        if(cabs[i]->getCabId()==id){
            return cabs[i];
        }
    }
    return NULL;
}

/**
 * get the trip
 * @return the trip with the given id, if not have return null;
 */
Trip *TaxiCenter::getTrip(int id){
    for(int i=0; i<trips.size();i++){
        if(trips[i]->getTripId()==id){
            return trips[i];
        }
    }
    return NULL;
}

/**
 * find and return the closest driver, if dont have one that avilable return
 * null.
 * @param start point of the trip
 * @return the closest driver, if dont have one that avilable return null.
 */
Driver* TaxiCenter::getClosestDriver(Point* start){
    int minSteps=this->bfs->getMap()->getRowsSize()*this->bfs->getMap()
            ->getColumnsSize()+1;
    Driver* closestDriver=NULL;
    for (vector<Driver *>::iterator itD = driversInfo.begin();
         itD != driversInfo.end(); itD++) {
        if ((*itD)->isAvailable()) {
            Point *driverLocation = (*itD)->getCurrentLocation();
            int numOfSteps = this->bfs->findNumOfSteps(start,
                                                       driverLocation);
            if (numOfSteps < minSteps) {
                minSteps = numOfSteps;
                closestDriver=*(itD);
            }
        }
    }
    return closestDriver;
}