#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3d lightDirection_p, Color color_p): Light(color_p){
    lightDirection = lightDirection_p.normalize();
}


Vector3d DirectionalLight::getDirection(){
    return lightDirection;
}


Color DirectionalLight::getColor(){
    return lightColor;
}
