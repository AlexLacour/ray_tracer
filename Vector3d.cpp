#include "Vector3d.h"

Vector3d::Vector3d(float x_p, float y_p, float z_p){
    x = x_p;
    y = y_p;
    z = z_p;
}


Vector3d::Vector3d(const Vector3d &v){
    x = v.x;
    y = v.y;
    z = v.z;
}


std::ostream &operator << (std::ostream &out, const Vector3d v){
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}


std::istream &operator >> (std::istream &in, Vector3d &v){
    in >> v.x >> v.y >> v.z;
    return in;
}


Vector3d Vector3d::operator + (const Vector3d &v2){
    return Vector3d(x + v2.x, y + v2.y, z + v2.z);
}


Vector3d Vector3d::operator - (const Vector3d &v2){
    return Vector3d(x - v2.x, y - v2.y, z - v2.z);
}


Vector3d Vector3d::operator = (const Vector3d &v2){
    x = v2.x;
    y = v2.y;
    z = v2.z;
    return *this;
}


Vector3d Vector3d::operator += (const Vector3d &v2){
    x += v2.x;
    y += v2.y;
    z += v2.z;
    return *this;
}


Vector3d Vector3d::operator -= (const Vector3d &v2){
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;
    return *this;
}


Vector3d Vector3d::operator * (const float k){
    x *= k;
    y *= k;
    z *= k;
    return *this;
}


bool Vector3d::operator == (const Vector3d &v2){
    if(x == v2.x && y == v2.y && z == v2.z){
        return true;
    }
    return false;
}


bool Vector3d::operator != (const Vector3d &v2){
    if(x == v2.x || y == v2.y || z == v2.z){
        return false;
    }
    return true;
}


float Vector3d::dot(const Vector3d v){
    return (x * v.x) + (y * v.y) + (z * v.z);
}


Vector3d Vector3d::cross(const Vector3d v){
    return Vector3d(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}


float Vector3d::getNorm(){
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}


Vector3d Vector3d::normalize(){
    float norm = this->getNorm();
    x = x / norm;
    y = y / norm;
    z = z / norm;
    return *this;
}
