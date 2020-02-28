#ifndef __DIRECTIONALLIGHT_H
#define __DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight: public Light{
    private:
        Vector3d lightDirection;
    public:
        DirectionalLight(Vector3d lightDirection_p, Color lightColor_p=Color(1, 1, 1));
        ~DirectionalLight(){}
        Vector3d getDirection();
        Color getColor();
};

#endif
