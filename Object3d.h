#ifndef __OBJECT3D_H
#define __OBJECT3D_H

#include "Color.h"
#include "Ray.h"

class Object3d{
    protected:
        Vector3d center;
        Color color;
        float ks;
        float nShiny;
        float kr;

    public:
        Object3d(Vector3d center_p, Color color_p, float ks_p, float nShiny_p, float kr_p);
        ~Object3d(){}
        virtual float getIntersectionDistance(Ray incidentRay) = 0;
        Color getColor();
        Vector3d getCenter();
        virtual Vector3d getNormalAt(Vector3d point) = 0;
        virtual bool hasTexture() = 0;
        virtual Color getColorTexture(Vector3d normalVector) = 0;
        float getKs();
        float getNs();
        float getKr();
};

#endif
