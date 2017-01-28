//
// Created by gili on 18/01/17.
//

#ifndef EX5_THREADPOOL_H
#define EX5_THREADPOOL_H

#include <iostream>
#include <queue>
#include <thread>
#include <pthread.h>
#include "Task.h"

using namespace std;
class ThreadPool {
private:
    int pool_size;
    pthread_t* threads;
    bool stop;
    pthread_mutex_t lock;
    queue<Task*> tasks;
public:
    ThreadPool(int size);

    ~ThreadPool();

    void doTasks();

    void* execute_thread();

    void addTask(Task* task);

    void terminate();

    queue<Task*> getTasks();

    bool isEmpty();
};


#endif //EX5_THREADPOOL_H

