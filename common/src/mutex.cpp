#include "mutex.hpp"

using namespace std;

Mutex::Mutex() {
    pthread_mutexattr_t attributes;
    pthread_mutexattr_init(&attributes);
    pthread_mutexattr_settype(&attributes,PTHREAD_MUTEX_RECURSIVE);

    if(pthread_mutex_init(&mutex,&attributes)!=0) {
	// error in mutex init	
	// we cannot use the logger, as the logger uses mutexes
	cout<<"Error while initializing a mutex. Exiting"<<endl;
	exit(EXIT_FAILURE);
    } 
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex);
}

void Mutex::lock() {
    pthread_mutex_lock(&mutex);
}

void Mutex::trylock() {
    pthread_mutex_trylock(&mutex);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&mutex);    
}

pthread_mutex_t* Mutex::get_mutex() {
    return &mutex;
}
