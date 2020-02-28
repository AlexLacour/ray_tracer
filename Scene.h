#include <string>
#include "Object3d.h"
#include <vector>

class Scene
{
    private:
        int dim_x;
        int dim_y;
        int dim_z;
        std::vector<Object3d*> objects;

    public:
        Scene(int dim_x_p=5, int dim_y_p=5, int dim_z_p=5);
        ~Scene(){}
        unsigned char* Render(unsigned int imgWidth, unsigned int imgHeight, Vector3d rayTracerOrigin);
        void addObject(Object3d* obj);
        Color getPixelColor(Ray camRay);
};
