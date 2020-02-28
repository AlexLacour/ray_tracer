#include "Object3d.h"

Object3d::Object3d(Vector3d center_p, Color color_p){
    center = center_p;
    color = color_p;
}


Color Object3d::getColor(){
    return color;
}
