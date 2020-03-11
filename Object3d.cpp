#include "Object3d.h"

Object3d::Object3d(Vector3d center_p, Color color_p, float ks_p, float nShiny_p, float kr_p){
    center = center_p;
    color = color_p;
    ks = ks_p;
    nShiny = nShiny_p;
    kr = kr_p;
}


Color Object3d::getColor(){
    return color;
}


Vector3d Object3d::getCenter(){
    return center;
}


float Object3d::getKs(){
    return ks;
}


float Object3d::getNs(){
    return nShiny;
}


float Object3d::getKr(){
    return kr;
}
