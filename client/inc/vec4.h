#ifndef DEF_VEC4
#define DEF_VEC4

#include <math.h>

template <class number>
class Vec4 {
public:
    Vec4(number =0,number =0,number =0,number =1);
    number x;
    number y;
    number z;
    number t;
    number norm();
    Vec4<number> normalize();
    Vec4<number> cross(Vec4<number> n);
    number scalar(Vec4<number> n);
    Vec4<number> operator+(Vec4<number> n);
    Vec4<number> operator-(Vec4<number> n);
    Vec4<number> operator*(Vec4<number> n);
    Vec4<number> operator*(number n);
    Vec4<number> operator/(number n);
private:
};

template <class number>
Vec4<number>::Vec4(number x,number y,number z,number t) : x(x), y(y), z(z), t(t) {
}

template <class number>
number Vec4<number>::norm() {
    return sqrt(x*x+y*y+z*z+t*t);
}

template <class number>
Vec4<number> Vec4<number>::normalize() {
    number val=norm();
    if(val!=0) {
        x/=val;
        y/=val;
        z/=val;
        t/=val;
    }
    return Vec4<number>(x,y,z,t);
}

template <class number>
Vec4<number> Vec4<number>::operator+(Vec4<number> n) {
    n.x+=x;
    n.y+=y;
    n.z+=z;
    n.t+=z;
    return n;
}

template <class number>
Vec4<number> Vec4<number>::operator-(Vec4<number> n) {
    Vec4<number> res;
    res.x=x-n.x;
    res.y=y-n.y;
    res.z=z-n.z;
    res.t=t-n.t;
    return res;
}

// vectorial product
template <class number>
Vec4<number> Vec4<number>::operator*(Vec4<number> n) {
    return cross(n);
}

template <class number>
Vec4<number> Vec4<number>::operator*(number n) {
    Vec4<number> res;
    res.x=x*n;
    res.y=y*n;
    res.z=z*n;    
    res.t=t*n;
    return res;
}

template <class number>
Vec4<number> Vec4<number>::operator/(number n) {
    Vec4<number> res;
    res.x=x/n;
    res.y=y/n;
    res.z=z/n;    
    res.t=t/n;
    return res;
}

//cross product (vector product)
template <class number>
Vec4<number> Vec4<number>::cross(Vec4<number> n) {
    Vec4<number> res;
    res.x=y*n.z-z*n.y;
    res.y=z*n.x-x*n.z;
    res.z=x*n.y-y*n.x;
    res.t=1;
    return res;
}

//scalar product (dot product)
template <class number>
number Vec4<number>::scalar(Vec4<number> n) {
    return n.x*x+n.y*y+n.z*z+n.t*t;
}

#endif
