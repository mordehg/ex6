//
// Created by yarden95c on 08/12/16.
//

#include "GameFlow.h"
#include "Udp.h"
#include "Tcp.h"

int option;
vector<bool> finish_10;
vector<bool> finishTrips;
//vector<ClientHandler*> handlers;
using namespace std;

class ClientHandler{
public:
    Socket* sock;
    TaxiCenter* taxiCenter;
    GameFlow* flow;
    int index;
    ClientHandler(Socket* inputSock, TaxiCenter* inputCenter, GameFlow* game,
                  int i) {
        this->sock = inputSock;
        this->taxiCenter = inputCenter;
        this->flow = game;
        this->index=i;
    }
    ~ClientHandler()   {
    }
};

vector<ClientHandler*> handlers;

class TripHandler{
public:
    GameFlow* flow;
    Trip* trip;
    int index;
    TripHandler(GameFlow* game, Trip* inputTrip, int i) {
        this->flow = game;
        this->trip = inputTrip;
        this->index = i;
    }
    ~TripHandler() { }
};

/**
 * constractur of game flow.
 * @param map map of the city
 * @return nothing
 */
GameFlow::GameFlow(int portNo1) {
    this->bfs = NULL;
    this->grid = NULL;
    this->taxiCenter = new TaxiCenter(this->bfs);
    this->comm = NULL;
    this->time = 0;
    this->driversNum=0;
    this->tripsNum=0;
    this->portNo = portNo1;
    this->validCheck = new Validation(true, this->taxiCenter);
    pthread_mutex_init(&this->connection_locker, 0);
    pthread_mutex_init(&this->list_locker, 0);
}

/**
 * destractur
 */
GameFlow::~GameFlow() {
    option=NULL;
    pthread_mutex_destroy(&this->connection_locker);
    pthread_mutex_destroy(&this->list_locker);
    delete(bfs);
    delete (comm);
    delete (taxiCenter);
    delete(validCheck);
    while(!handlers.empty()||!finish_10.empty()){
        ClientHandler *c=handlers.back();
        handlers.pop_back();
        delete (c);
        finish_10.pop_back();
    }


}

vector<string> GameFlow::inputParser() {
    vector<string> data;
    string input;
    cin >> input;
    int startPos = 0;
    int i = 0;
    string current_str;
    while (input.length() != i) {
        if (input[i] == ',') {
            int len = i-startPos;
            current_str = input.substr(startPos,len);
            data.push_back(current_str);
            startPos = i+1;
        }
        i++;
    }
    current_str = input.substr(startPos,i-startPos+1);
    data.push_back(current_str);
    return data;
}

void GameFlow::establishCommunication(string str) {
    if (str=="UDP"){
        comm = new Udp(true, portNo);
    }
    else if (str=="TCP"){
        comm = new Tcp(true, portNo);
    }

}

/**
 * menu optinos of program
 */
void GameFlow::startGame() {
    int sizeX, sizeY, numOfObstacles;
    do {
        cin >> sizeX >> sizeY;
    } while (!this->validCheck->validMap(sizeX,sizeY));
    // create matrix.
    Matrix matrix(sizeX, sizeY);
    //Matrix matrix(6, 6);
    // save matrix address at map object.
    this->grid = &matrix;
    this->bfs = new Bfs(this->grid);
    //set obstacles
    do {
        cin >> numOfObstacles;
    } while (!this->validCheck->validObst(this->grid, numOfObstacles));
    if (numOfObstacles > 0) {
        this->grid->setObstacles(numOfObstacles);
    }
    int choice;
    cin >> choice;
    option = choice;
    while (choice != 7) {
        switch (choice) {
            case 1:
                this->recieveDrivers();
                break;
            case 2:
                finishTrips.push_back(false);
                this->insertARide();
                break;
            case 3:
                this->insertAVehicle();
                break;
            case 4:
                this->printDriverLocation();
                break;
            case 9:
                this->moveTheClock();
                //this->sendClientNewLocation();
            default:
                cout << "-1" << endl;
                break;
        }
        cin >> choice;
    }
    //do join and exit from all threads
    for(int i=0; i<this->driversNum;i++){
        this->killTheClient(i);
        //pthread_join(this->threads[i], NULL);
    }
}


void *test(void* ptr){
    char buffer[9999];
    ClientHandler* handler = (ClientHandler*)ptr;
    handler->sock->reciveData(buffer, sizeof
    (buffer), handler->index);
    Driver *d2;
    boost::iostreams::basic_array_source<char> device(buffer,
                                                      sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(
            device);
    boost::archive::binary_iarchive ia(s);
    ia >> d2;
    int driverId=d2->getDriverId();
    pthread_mutex_lock(&handler->flow->list_locker);
    handler->taxiCenter->addDriverInfo(d2);
    pthread_mutex_unlock(&handler->flow->list_locker);
    //send the cab

    Cab *cab = handler->taxiCenter->getDriver(driverId)->getCab();
    string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std
    ::string> > stream(inserter);
    boost::archive::binary_oarchive oa(stream);
    oa << cab;
    stream.flush();
    handler->sock->sendData(serial_str, handler->index);
    while (option != 7) {
        if (option == 10 && !finish_10[handler->index]) {
            Point *newLocation = handler->taxiCenter->getDriver(driverId)
                    ->getCurrentLocation();
            string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
                    s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << newLocation;
            s.flush();
            pthread_mutex_lock(&handler->flow->list_locker);
            handler->sock->sendData(serial_str, handler->index);
            finish_10[handler->index]=true;
            pthread_mutex_unlock(&handler->flow->list_locker);
        }
    }
    pthread_exit(ptr);
}

void *createBfsForTrip(void* ptr) {
    TripHandler* handlerT = (TripHandler*)ptr;
    pthread_mutex_lock(&handlerT->flow->list_locker);
    if(!handlerT->trip->setPath()){
        handlerT->flow->getCenter()->popTrip(handlerT->index);
        handlerT->flow->decreaseTripNum();
        handlerT->flow->popFinishTrips(handlerT->index);
    }
    else{
        finishTrips[handlerT->index] = true;
    }
    pthread_mutex_unlock(&handlerT->flow->list_locker);
    pthread_exit(ptr);
}

/**
 * get a new driver from the client, set him a car and send the cab to the
 * client.
 */
void GameFlow::recieveDrivers() {
    int numOfDrivers;
    cin >> numOfDrivers;
    char buffer[9999];
    this->establishCommunication("TCP");
    this->comm->initialize();
    int tripIndex=this->tripsNum;
    for (int i=0; i<numOfDrivers;i++) {
        this->comm->acceptClient();
        ClientHandler* handler = new ClientHandler(this->comm,
                                                   this->taxiCenter, this, i);
        handlers.push_back(handler);
        pthread_create(&this->threads[i], NULL, test, (void*)handler);
        //pthread_join(this->threads[i], NULL);
        finish_10.push_back(true);
    }
    this->driversNum=numOfDrivers;
    this->tripsNum=tripIndex;
}

bool GameFlow::buildTrip() {
    int id, xStart, yStart, xEnd, yEnd, numOfPassengers, startTime;
    double tariff;
    vector<string> trip_data;
    trip_data = this->inputParser();
    if (this->validCheck->validTripLength(trip_data.size())){
        id = atoi(trip_data[0].c_str());
        xStart = atoi(trip_data[1].c_str());
        yStart = atoi(trip_data[2].c_str());
        xEnd = atoi(trip_data[3].c_str());
        yEnd = atoi(trip_data[4].c_str());
        numOfPassengers = atoi(trip_data[5].c_str());
        tariff = (double) atoi(trip_data[6].c_str());
        startTime = atoi(trip_data[7].c_str());
        if(this->validCheck->validTrip(this->bfs->getMap(),id,xStart,yStart,
                                       xEnd,yEnd,numOfPassengers,tariff,startTime)){
            Point *start = new Point(xStart, yStart);
            Point *end = new Point(xEnd, yEnd);
            Trip *trip = new Trip(this->bfs, id, start, end, numOfPassengers, tariff,
                                  startTime);
            taxiCenter->addTrip(trip);
            start = NULL;
            end = NULL;
            trip=NULL;
            return true;
        }
    }
    return false;
}


/**
 * insert a new trip to the trips in the taxi center
 * trip doesn't have a driver yet, only in choice 6 we add a driver to
 * each trip
 */
void GameFlow::insertARide() {
    if(this->buildTrip()){
        int tripIndex=this->tripsNum;
        Trip* trip=taxiCenter->getTrips()[tripIndex];
        int numDrivers=this->driversNum;
        TripHandler* handler = new TripHandler(this,trip,tripIndex);
        pthread_create(&this->threadsTrip[tripIndex], NULL, createBfsForTrip,
                       (void*)handler);
        this->tripsNum=tripIndex+1;
        this->driversNum=numDrivers;
        // set the pointers to point on null so when
        // the objects will delete those pointers will no longer point on them
    }
    else{
        popFinishTrips(this->tripsNum);
    }
}

/**
 * insert a new vehicle to the cabs in the taxi center
 */
void GameFlow::insertAVehicle() {
    vector<string> cab_data;
    int id, taxiType;
    char manufacturerLetter, colorLetter, c;
    enum Color color;
    enum CarType carType;
    cab_data = this->inputParser();
    if(this->validCheck->validCabLength(cab_data.size())){
        id = atoi(cab_data[0].c_str());
        taxiType = atoi(cab_data[1].c_str());
        manufacturerLetter = cab_data[2].c_str()[0];
        colorLetter = cab_data[3].c_str()[0];
        color = Color(colorLetter);
        carType = CarType(manufacturerLetter);
        if(this->validCheck->validCab(id, taxiType, carType, color)){
            Cab* cab = new Cab(id, carType, color, taxiType, 1);
            taxiCenter->addCab(cab);
            cab = NULL;
        }
    }
}

/**
 *printing the currrent location of a specific driver
 */
void GameFlow::printDriverLocation() {
    vector<string> driverId_data;
    int driverId;
    driverId_data = this->inputParser();
    if(this->validCheck->validDriverIdLength(driverId_data.size())){
        driverId = atoi(driverId_data[0].c_str());
        if(this->validCheck->validDriverId(driverId)){
            cout << *(taxiCenter->getDriver(driverId)->getCurrentLocation())
                 <<endl;
        }
    }
}

/**
 * move the clock + 1
 * check with all the trips, if it is their start time, connect them to a driver
 * if their time passed make them to move one step
 */
void GameFlow::moveTheClock() {
    while(!isFinish10() && !isFinishBuildThread()) { }
    // bfs threads are over - need to add
    vector<Trip *> trips = taxiCenter->getTrips();
    vector<Driver *> drivers = taxiCenter->getDriversInfo();
    for (int i = 0; i < trips.size(); i++) {
        if (trips[i]->getStartTime() == time) {
            trips[i]->setDriver(this->taxiCenter->getClosestDriver(
                    trips[i]->getStartPoint()));
        }
        if (trips[i]->getStartTime() <= time && !trips[i]->getPath()
                ->empty()) {
            trips[i]->moveOneStep();
        } else if (trips[i]->getPath()->empty()) {
            trips[i]->getDriver()->setAvailable(true);
            taxiCenter->popTrip(i);
        }
    }
    time++;
    resetFinish10();
    option = 10;
}


/**
 * after 7, we need to finish the program so send the client a null and it
 * will die too.
 */
void GameFlow::killTheClient(int i) {
    Point *newLocation = NULL;
    string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
            inserter);
    boost::archive::binary_oarchive oa(s);
    oa << newLocation;
    s.flush();
    comm->sendData(serial_str,i);
}

bool GameFlow::isFinish10(){
    bool all=true;
        for(int i=0; i<finish_10.size(); i++){
            if(finish_10[i]==false){
                all=false;
                break;
            }
        }
        return all;
    }

bool GameFlow::isFinishBuildThread() {
    bool all=true;
    for(int i=0; i < this->tripsNum; i++){
        if(finishTrips[i]==false){
            all=false;
            break;
        }
    }
    return all;
}

void GameFlow::popFinishTrips(int i) {
    vector<bool> temp;
    int j=0;
    while (!finishTrips.empty()) {
        if(i==j){
            finishTrips.pop_back();
        }
        else{
            temp.push_back(finishTrips.back());
            finishTrips.pop_back();
        }
        j++;
    }
    while (!temp.empty()) {
        finishTrips.push_back((temp.back()));
        temp.pop_back();
    }
}


void GameFlow::resetFinish10(){
    for(int i=0; i<finish_10.size(); i++){
        finish_10[i]=false;
    }
}

TaxiCenter* GameFlow::getCenter(){
    return this->taxiCenter;
}

void GameFlow::decreaseTripNum(){
    this->tripsNum--;
}

Map* GameFlow::getMap(){
    return this->grid;
}