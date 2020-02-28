#include "Ray.h"

Ray::Ray(Vector3d origin_p, Vector3d dir_p){
    origin = origin_p;
    dir = dir_p.normalize();
}


Vector3d Ray::getOrigin(){
    return origin;
}


Vector3d Ray::getDir(){
    return dir;
}
