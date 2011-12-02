#ifndef DEF_VEC4
#define DEF_VEC4

#include <math.h>

template <class number>
class Vec4 {
public:
    Vec3(number =0,number =0,number =0,number =1);
    number x;
    number y;
    number z;
    number t;
    number norm();
    Vec3<number> normalize();
    Vec3<number> cross(Vec3<number> n);
    number scalar(Vec3<number> n);
    Vec3<number> operator+(Vec3<number> n);
    Vec3<number> operator-(Vec3<number> n);
    Vec3<number> operator*(Vec3<number> n);
    Vec3<number> operator*(number n);
private:
};

template <class number>
Vec3<number>::Vec3(number x,number y,number z,number t) : x(x), y(y), z(z), t(t) {
}

template <class number>
number Vec3<number>::norm() {
    return sqrt(x*x+y*y+z*z);
}

template <class number>
Vec3<number> Vec3<number>::normalize() {
    number val=norm();
    if(val!=0) {
        x/=val;
        y/=val;
        z/=val;
    }
    return Vec3<number>(x,y,z);
}

template <class number>
Vec3<number> Vec3<number>::operator+(Vec3<number> n) {
    n.x+=x;
    n.y+=y;
    n.z+=z;
    return n;
}

template <class number>
Vec3<number> Vec3<number>::operator-(Vec3<number> n) {
    Vec3<number> res;
    res.x=x-n.x;
    res.y=y-n.y;
    res.z=z-n.z;
    return res;
}

// vectorial product
template <class number>
Vec3<number> Vec3<number>::operator*(Vec3<number> n) {
    Vec3<number> res;
    res.x=(y*n.z-z*n.y);
    res.y=(z*n.x-x*n.z);
    res.z=(x*n.y-y*n.x);
    return res;
}

template <class number>
Vec3<number> Vec3<number>::operator*(number n) {
    Vec3<number> res;
    res.x=x*n;
    res.y=y*n;
    res.z=z*n;
    return res;
}

//cross product
template <class number>
Vec3<number> Vec3<number>::cross(Vec3<number> n) {
    Vec3<number> res;
    res.x=y*n.z-z*n.y;
    res.y=z*n.x-x*n.z;
    res.z=x*n.y-y*n.x;
    return res;
}

//cross product
template <class number>
number Vec3<number>::scalar(Vec3<number> n) {
    return n.x*x+n.y*y+n.z*z;
}

#endif
