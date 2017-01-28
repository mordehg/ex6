//
// Created by gili on 18/01/17.
//

#ifndef EX5_TASK_H
#define EX5_TASK_H

#include <iostream>
#include <thread>
#include <pthread.h>

/*class TripHandler{
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
};*/


class Task {
private:
    void *arg;
    void* (*func)(void* args);

public:
    Task(void * (*func)(void *arg), void* arg);

    ~Task();

    void execute();

};

#endif //EX5_TASK_H
