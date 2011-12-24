#ifndef DEF_Vec3
#define DEF_Vec3

#include <math.h>

template <class number>
class Vec3 {
public:
    Vec3(number =0,number =0,number =0);
    number x;
    number y;
    number z;
    number norm() const;
    Vec3<number> normalize() const;
    Vec3<number> cross(Vec3<number> n);
    number scalar(Vec3<number> n) const;
    Vec3<number> operator+(Vec3<number> n);
    Vec3<number> operator-(Vec3<number> n);
    Vec3<number> operator*(Vec3<number> n);
    Vec3<number> operator*(number n);
    Vec3<number> operator/(number n);
    Vec3<number> rotate(float angle, Vec3<number> axis);
private:
};

template <class number>
Vec3<number>::Vec3(number x,number y,number z) : x(x), y(y), z(z) {
}

template <class number>
number Vec3<number>::norm() const {
    return sqrt(x*x+y*y+z*z);
}

template <class number>
Vec3<number> Vec3<number>::normalize() const{
    number val=norm();
    Vec3<number> result = Vec3<number>();
    if(val!=0) {
        result.x = x/val;
        result.y = y/val;
        result.z = z/val;
    }
    return result;
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
    return cross(n);
}

template <class number>
Vec3<number> Vec3<number>::operator*(number n) {
    Vec3<number> res;
    res.x=x*n;
    res.y=y*n;
    res.z=z*n;
    return res;
}

template <class number>
Vec3<number> Vec3<number>::operator/(number n) {
    Vec3<number> res;
    res.x=x/n;
    res.y=y/n;
    res.z=z/n;
    return res;
}

//cross product (vector product)
template <class number>
Vec3<number> Vec3<number>::cross(Vec3<number> n) {
    Vec3<number> res;
    res.x=y*n.z-z*n.y;
    res.y=z*n.x-x*n.z;
    res.z=x*n.y-y*n.x;
    return res;
}

//scalar product (dot product)
template <class number>
number Vec3<number>::scalar(Vec3<number> n) const {
    return n.x*x+n.y*y+n.z*z;
}

// phi : angle in degrees
template <class number>
Vec3<number> Vec3<number>::rotate(float phi, Vec3<number> axis) {
    phi = phi * 3.14159265  / 180; // angle in radians
    return (*this) * (float)(cos(phi)) + (float)(1-cos(phi)) * this->scalar(axis) + axis.cross(*this) * (float)(sin(phi));
}

#endif
