#include "conditional.h"

using namespace std;

Conditional::Conditional() {
    if(pthread_cond_init(&cond,NULL)!=0) {
        cout<<"Error while initializing a condition variable. Exiting"<<endl;
        exit(EXIT_FAILURE);
    }
}

Conditional::~Conditional() {
    pthread_cond_destroy(&cond);
}

void Conditional::wait() {
    mut.lock();
    pthread_cond_wait(&cond,mut.get_mutex());
    mut.unlock();
}

void Conditional::signal() {
    mut.lock();
    pthread_cond_signal(&cond);
    mut.unlock();
}
