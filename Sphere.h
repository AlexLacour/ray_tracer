#ifndef __SPHERE_H
#define __SPHERE_H

#include "Object3d.h"
#include "Ray.h"
#include "Color.h"
#include <cmath>

class Sphere: public Object3d{
    private:
        float R;
        unsigned char* textureMap;
        bool hasTextureAtt;
        int textureWidth;
        int textureHeight;

    public:
        Sphere(Vector3d center_p, float R_p, Color color_p=Color(0, 0, 1), float ks_p=0.0, float nShiny_p=0.0, float kr_p=0.0);
        float getIntersectionDistance(Ray incidentRay);
        Vector3d getNormalAt(Vector3d point);
        Color getColorTexture(Vector3d normalVector);
        void loadTexture(unsigned char* texMap_p, int texWidth, int texHeight);
        bool hasTexture();
};

#endif
