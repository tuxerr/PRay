#ifndef DEF_Vec3
#define DEF_Vec3

#include <cmath>

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
  void operator+=(Vec3<number> n);
  Vec3<number> operator-(Vec3<number> n);
  void operator-=(Vec3<number> n);
  Vec3<number> operator*(Vec3<number> n);
  Vec3<number> operator*(number n);
  Vec3<number> operator/(number n);
  bool operator==(Vec3<number> n);
  bool operator!=(Vec3<number> n);
  Vec3<number> rotate(float angle, Vec3<number> axis);
  Vec3<number> symmetry(Vec3<number> x);
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
void Vec3<number>::operator+=(Vec3<number> n) {
  x+=n.x;
  y+=n.y;
  z+=n.z;
}

template <class number>
Vec3<number> Vec3<number>::operator-(Vec3<number> n) {
  Vec3<number> res;
  res.x=x-n.x;
  res.y=y-n.y;
  res.z=z-n.z;
  return res;
}

template <class number>
void Vec3<number>::operator-=(Vec3<number> n) {
  x-=n.x;
  y-=n.y;
  z-=n.z;
}

template <class number>
bool Vec3<number>::operator==(Vec3<number> n) {
  return fabs(x-n.x)<0.00001 && fabs(y-n.y)<0.00001 && fabs(z-n.z)<0.00001;
}

template <class number>
bool Vec3<number>::operator!=(Vec3<number> n) {
  return !(operator!=(n));
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

// Rodrigues' rotation formula
// phi : angle in degrees
// axis : must be of norm 1
template <class number>
Vec3<number> Vec3<number>::rotate(float phi, Vec3<number> axis) {
  phi = phi * 3.14159265  / 180.0; // angle in radians
  return (*this) * cos(phi)
    + axis * (*this) * sin(phi)
    + axis * axis.scalar(*this) * ((float)1.0 - cos(phi)) ;
       
}

template <class number>
Vec3<number> Vec3<number>::symmetry(Vec3<number> x) {
  return x*(2*(*this).scalar(x)) + (*this)*(-1);
}

#endif
