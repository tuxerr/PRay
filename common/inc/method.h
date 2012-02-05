#ifndef DEF_METHOD
#define DEF_METHOD

// constructor is called  : Method<C> met(instance,&C::func_name);

template <class C>
class Method {
public:
    Method(C &ptr,void (C::*met)(void)) :  ptr(ptr), met(met)  {
        
    }
    void call() {
        (ptr.*met)();
    }
    
private:
    C &ptr;
    void (C::*met)(void);
};

#endif


