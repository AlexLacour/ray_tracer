#include "Scene.h"

Scene::Scene(int dim_x_p, int dim_y_p, int dim_z_p){
    dim_x = dim_x_p;
    dim_y = dim_y_p;
    dim_z = dim_z_p; 
}


Object3d* Scene::getNearestObject(Ray camRay, float &distance){
    std::vector<std::vector<float>> objectsDistances;
    for(unsigned int objId=0; objId<objects.size(); objId++){
        if(objects[objId]->getIntersectionDistance(camRay) >= 0){
            std::vector<float> objectDistance;
            objectDistance.push_back((float)objId);
            objectDistance.push_back(objects[objId]->getIntersectionDistance(camRay));

            objectsDistances.push_back(objectDistance);
        }
    }

    if(objectsDistances.size() > 0){
        float minDistance = objectsDistances[0][1];
        int minDistanceId = (int)objectsDistances[0][0];
        for(unsigned int objDisId=0; objDisId<objectsDistances.size(); objDisId++){
            if(objectsDistances[objDisId][1] < minDistance){
                minDistance = objectsDistances[objDisId][1];
                minDistanceId = (int)objectsDistances[objDisId][0];
            }
        }
        distance = minDistance;
        return objects[minDistanceId];
    }
    return NULL;
}


Color Scene::RayTrace(Ray camRay){
    // Find Nearest Object
    float distance;
    Object3d* nearestObject = getNearestObject(camRay, distance);
    Color pixelColor;
    if(nearestObject){
        // Get Object Color
        pixelColor = nearestObject->getColor();
        for(unsigned int lightId=0; lightId<lights.size(); lightId++){
            Vector3d lightDir = lights[lightId]->getDirection();
            Vector3d toLight = (lightDir * (-1));
            Vector3d spherePoint = camRay.getOrigin() + (camRay.getDir() * distance);
            Vector3d normalVector = nearestObject->getNormalAt(spherePoint);
            float nScalarL = normalVector.dot(toLight);
            if(nScalarL < 0){
                nScalarL = 0;
            }
            std::cout << nScalarL << " ";
            pixelColor = (pixelColor * lights[lightId]->getColor()) * nScalarL;
        }
    }
    return pixelColor;
}


unsigned char* Scene::Render(unsigned int imgWidth, unsigned int imgHeight, Vector3d rayTracerOrigin){
    unsigned char* buffer = new unsigned char[imgWidth * imgHeight * 3];
    for(int w=0; w<imgWidth; w++){
        for(int h=0; h<imgHeight; h++){
            Vector3d bufferPoint((double)(w - (int)(imgWidth / 2)) / (double)imgWidth,
                                 (double)(h - (int)(imgHeight / 2)) / (double)imgHeight,
                                 0);
            Vector3d rayDir = bufferPoint - rayTracerOrigin;

            Ray camRay(rayTracerOrigin, rayDir);
            Color PixelColor = RayTrace(camRay);
            buffer[(h * imgWidth + w) * 3 + 0] = PixelColor.b * PixelColor.a * 255.0;
            buffer[(h * imgWidth + w) * 3 + 1] = PixelColor.g * PixelColor.a * 255.0;
            buffer[(h * imgWidth + w) * 3 + 2] = PixelColor.r * PixelColor.a * 255.0;
        }
    }
    return buffer;
}


void Scene::addObject(Object3d* obj){
    objects.push_back(obj);
}


void Scene::addLight(Light* light){
    lights.push_back(light);
}
