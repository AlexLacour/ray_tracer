#include "Sphere.h"

Sphere::Sphere(Vector3d center_p, float R_p, Color color_p, float ks_p, float nShiny_p, float kr_p)
: Object3d(center_p, color_p, ks_p, nShiny_p, kr_p){
    R = R_p;
    hasTextureAtt = false;
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
    if(delta > 0){
        t1 = (- b + sqrt(delta)) / (2 * a);
        t2 = (- b - sqrt(delta)) / (2 * a);
        if(t1 > 0 && t2 > 0){
            t = std::min(t1, t2);
        }
        else if(t1 < 0  && t2 > 0){
            t = t2;
        }
        else if(t2 < 0  && t1 > 0){
            t = t1;
        }
        return t;
    }
    else if(delta == 0){
        float t_p = (-b / (2 * a));
        if(t_p > 0){
            t = t_p;
            return  t;
        }
    }
    return t;
}


Vector3d Sphere::getNormalAt(Vector3d point){
    return (point - center).normalize();
}


void Sphere::loadTexture(unsigned char* texMap_p, int texWidth, int texHeight){
    textureMap = texMap_p;
    hasTextureAtt = true;
    textureWidth = texWidth;
    textureHeight = texHeight;
}


Color Sphere::getColorTexture(Vector3d normalVector){
    float u = std::asin(normalVector.x) / M_PI + 0.5;
    float v = std::asin(normalVector.y) / M_PI + 0.5;

    int b = textureMap[((int)(textureHeight * v) * textureWidth + (int)(textureWidth * u)) * 3 + 0];
    int g = textureMap[((int)(textureHeight * v) * textureWidth + (int)(textureWidth * u)) * 3 + 1];
    int r = textureMap[((int)(textureHeight * v) * textureWidth + (int)(textureWidth * u)) * 3 + 2];

    return Color(r, g, b);
}


bool Sphere::hasTexture(){
    return hasTextureAtt;
}