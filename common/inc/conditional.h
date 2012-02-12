#ifndef DEF_CONDITIONAL
#define DEF_CONDITIONAL

#include <iostream>
#include "mutex.h"
#include <pthread.h>
#include <stdlib.h>

class Conditional {
public:
    Conditional();
    ~Conditional();
    void wait();
    void signal();

private:
    Mutex mut;
    pthread_cond_t cond;
};

#endif
