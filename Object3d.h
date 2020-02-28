#include "Ray.h"
#include "Color.h"

class Object3d
{
    protected:
        Vector3d center;
        Color color;

    public:
        Object3d(Vector3d center_p, Color color_p);
        ~Object3d(){}
        virtual float getIntersectionDistance(Ray incidentRay) = 0;
        Color getColor();
};

class Sphere: public Object3d{
    private:
        float R;
    public:
        Sphere(Vector3d center_p, float R_p, Color color_p=Color(0, 0, 255));
        float getIntersectionDistance(Ray incidentRay);
};
