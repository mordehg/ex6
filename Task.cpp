//
// Created by gili on 18/01/17.
//

#include "Task.h"

/*void* createBfsForTrip(void* ptr) {
    TripHandler* handlerT = (TripHandler*)ptr;
    pthread_mutex_lock(&handlerT->flow->list_locker);
    handlerT->trip->setPath();
    //finishTrips[handlerT->index] = true;
    pthread_mutex_unlock(&handlerT->flow->list_locker);
    pthread_exit(ptr);
}*/

Task::Task(void * (*func)(void *arg), void* arg) {
    this->func = func;
    this->arg = arg;
}

Task::~Task() { }

void Task::execute() {
    this->func(this->arg);
}