#ifndef DEF_MUTEX
#define DEF_MUTEX

#include <iostream>
#include "logger.h"
#include <pthread.h>
#include <stdlib.h>

#define DEFAULT_RECURSIVE true

/* C++ object oriented mutex overlay */
class Mutex {
 public:
    Mutex();
    ~Mutex();
    void lock();
    void trylock();
    void unlock();

 private:
    pthread_mutex_t mutex;
};

#endif
