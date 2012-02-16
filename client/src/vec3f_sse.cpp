#include "vec3f_sse.hpp"
#include "logger.hpp"

// Rodrigues' rotation formula
// phi : angle in degrees
// axis : must be of norm 1
Vec3f Vec3f::rotate(float phi, Vec3f axis) {
    phi = phi * 3.14159265  / 180.0; // angle in radians
    return (*this) * cos(phi)
        + axis * (*this) * sin(phi)
        + axis * axis.scalar(*this) * ((float)1.0 - cos(phi)) ;   
}

Vec3f Vec3f::symmetry(Vec3f x) {
    return x*(2*(*this).scalar(x)) + (*this)*(-1);
}

void Vec3f::printLog() {
    float coord[4];
    getCoord(coord);
    Logger::log(LOG_DEBUG)<<"x="<<coord[0]<<std::endl;
    Logger::log(LOG_DEBUG)<<"y="<<coord[1]<<std::endl;
    Logger::log(LOG_DEBUG)<<"z="<<coord[2]<<std::endl;
    Logger::log(LOG_DEBUG)<<"t="<<coord[3]<<std::endl;
}

bool Vec3f::equals(Vec3f vec) {
    float coord1[4];
    getCoord(coord1);
    float coord2[4];
    vec.getCoord(coord2);
    return (abs(coord1[0] - coord2[0]) < 1e-5)
        && (abs(coord1[1] - coord2[1]) < 1e-5)
        && (abs(coord1[2] - coord2[2]) < 1e-5)
        && (abs(coord1[3] - coord2[3]) < 1e-5);
}
