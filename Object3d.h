#ifndef __OBJECT3D_H
#define __OBJECT3D_H

#include "Color.h"
#include "Ray.h"

class Object3d{
    protected:
        Vector3d center;
        Color color;

    public:
        Object3d(Vector3d center_p, Color color_p);
        ~Object3d(){}
        virtual float getIntersectionDistance(Ray incidentRay) = 0;
        Color getColor();
        virtual Vector3d getNormalAt(Vector3d point) = 0;
};

#endif
