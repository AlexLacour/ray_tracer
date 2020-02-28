#ifndef __SPHERE_H
#define __SPHERE_H

#include "Object3d.h"
#include "Ray.h"
#include "Color.h"

class Sphere: public Object3d{
    private:
        float R;
    public:
        Sphere(Vector3d center_p, float R_p, Color color_p=Color(0, 0, 1));
        float getIntersectionDistance(Ray incidentRay);
        Vector3d getNormalAt(Vector3d point);
};

#endif
