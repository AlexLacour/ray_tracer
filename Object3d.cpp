#include "Object3d.h"

Object3d::Object3d(Vector3d center_p, Color color_p){
    center = center_p;
    color = color_p;
}


Color Object3d::getColor(){
    return color;
}


Sphere::Sphere(Vector3d center_p, float R_p, Color color_p)
: Object3d(center_p, color_p){
    R = R_p;
}


float Sphere::getIntersectionDistance(Ray incidentRay){
    // Points
    Vector3d src_point = incidentRay.getOrigin();

    //Vectors
    Vector3d dir = incidentRay.getDir();

    //t-Computing
    Vector3d sphere_to_point = src_point - center;

    float a = 1;
    float b = 2 * (dir.dot(sphere_to_point));
    float c = sphere_to_point.dot(sphere_to_point) - pow(R, 2);

    float delta = pow(b, 2) - (4 * a * c);

    float t1, t2, t;
    t = -1;
    if(delta >= 0){
        t1 = (- b + sqrt(delta)) / (2 * a);
        t2 = (- b - sqrt(delta)) / (2 * a);
        if(t1 >= 0 && t2 >= 0){
            t = std::min(t1, t2);
        }
        else if(t1 < 0  && t2 >= 0){
            t = t2;
        }
        else if(t2 < 0  && t1 >= 0){
            t = t1;
        }
    }
    return t;
}
