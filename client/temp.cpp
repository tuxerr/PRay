template<typename T> 
class Ray { 
public: 
    Ray(Vec3<T> orig, Vec3<T> dir) : 
        orig(orig), dir(dir), txmin(T(0)), txmax(std::numeric_limits<T>::max()) 
    { 
        invdir = T(1) / dir; 
        sign[0] = (invdir.x < 0); 
        sign[1] = (invdir.y < 0); 
        sign[2] = (invdir.z < 0); 
    } 
    Vec3<T> orig, dir;      /// ray orig and dir 
    mutable T txmin, txmax; /// ray min and max distances 
    Vec3<T> invdir; 
    int sign[3]; 
};

bool intersect(const Ray<T> &r) const { 
    T txmin, txmax, tymin, tymax, tzmin, tzmax; 
    txmin = (bounds[r.sign[0]].x - r.orig.x) * r.invdir.x; 
    txmax = (bounds[1-r.sign[0]].x - r.orig.x) * r.invdir.x; 
    tymin = (bounds[r.sign[1]].y - r.orig.y) * r.invdir.y; 
    tymax = (bounds[1-r.sign[1]].y - r.orig.y) * r.invdir.y; 
    if ((txmin > tymax) || (tymin > txmax)) 
        return false; 
    if (tymin > txmin) 
        txmin = tymin; 
    if (tymax < txmax) 
        txmax = tymax; 
    tzmin = (bounds[r.sign[2]].z - r.orig.z) * r.invdir.z; 
    tzmax = (bounds[1-r.sign[2]].z - r.orig.z) * r.invdir.z; 
    if ((txmin > tzmax) || (tzmin > txmax)) 
        return false; 
    if (tzmin > txmin) 
        txmin = tzmin; 
    if (tzmax < txmax) 
        txmax = tzmax; 
    if (txmin > r.txmin) 
        r.txmin = txmin; 
    if (txmax < r.txmax) 
        r.txmax = txmax; 
    return true; 
}
