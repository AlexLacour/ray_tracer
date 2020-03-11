#ifndef __SCENE_H
#define __SCENE_H

#include <string>
#include <vector>
#include <cstdlib>
#include "Sphere.h"
#include "DirectionalLight.h"

class Scene
{
    private:
        int dim_x;
        int dim_y;
        int dim_z;
        std::vector<Object3d*> objects;
        std::vector<Light*> lights;

    public:
        Scene(int dim_x_p=5, int dim_y_p=5, int dim_z_p=5);
        ~Scene(){}
        unsigned char* Render(unsigned int imgWidth, unsigned int imgHeight, Vector3d rayTracerOrigin, int numberRays);
        void addObject(Object3d* obj);
        void addLight(Light* light);
        Color RayTrace(Ray camRay, int recursiveDepth);
        Object3d* getNearestObject(Ray camRay, float &distance);
};

#endif
