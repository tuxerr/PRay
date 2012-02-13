#ifndef DEF_MUTEX
#define DEF_MUTEX

#include <iostream>
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
    pthread_mutex_t* get_mutex();

 private:
    pthread_mutex_t mutex;
};

#endif
