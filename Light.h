#ifndef __LIGHT_H
#define __LIGHT_H

#include "Color.h"
#include "Vector3d.h"

class Light{
    protected:
        Color lightColor;

    public:
        Light(Color lightColor_p);
        ~Light(){}
        virtual Color getColor() = 0;
        virtual Vector3d getDirection() = 0;
};

#endif
