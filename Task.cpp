//
// Created by gili on 18/01/17.
//

#include "Task.h"

Task::Task(void * (*func)(void *arg), void* arg) {
    this->func = func;
    this->arg = arg;
}

Task::~Task() { }

void Task::execute() {
    this->func(this->arg);
}