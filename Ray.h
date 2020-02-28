#include "Vector3d.h"

class Ray
{
    private:
        Vector3d origin;
        Vector3d dir;
    public:
        Ray(Vector3d origin_p, Vector3d dir_p);
        ~Ray(){}
        Vector3d getOrigin();
        Vector3d getDir();
};
