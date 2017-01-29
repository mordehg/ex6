#include <unistd.h>
#include "ThreadPool.h"
static void *startTasks(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    pool->doTasks();
    return NULL;
}

ThreadPool::ThreadPool(int threads_num) {
    this->threads = new pthread_t[threads_num];
    this->pool_size = threads_num;
    this->stop = false;
    pthread_mutex_init(&lock, 0);
    for (int i = 0; i < threads_num; i++) {
        pthread_create(threads + i, NULL, startTasks, this);
    }
}

ThreadPool::~ThreadPool() {
    this->terminate();
    //delete[] this->threads;
    pthread_mutex_destroy(&this->lock);
}


void ThreadPool::doTasks() {
    while (!this->stop) {
        pthread_mutex_lock(&this->lock);
        if (!this->tasks.empty()) {
            Task* task = this->tasks.front();
            this->tasks.pop();
            pthread_mutex_unlock(&lock);
            task->execute();
        }
        else {
            pthread_mutex_unlock(&this->lock);
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

void ThreadPool::addTask(Task *task) {
    this->tasks.push(task);
}


void ThreadPool::terminate() {
    this->stop = true;
    for (int i = 0; i < this->pool_size; i++) {
        pthread_join(*(this->threads + i), NULL);
    }
}

queue<Task*> ThreadPool::getTasks(){
    return this->tasks;
}

/*bool ThreadPool::isEmpty() {

}*/