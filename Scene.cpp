#include "Scene.h"

Scene::Scene(int dim_x_p, int dim_y_p, int dim_z_p){
    dim_x = dim_x_p;
    dim_y = dim_y_p;
    dim_z = dim_z_p; 
}


Color Scene::getPixelColor(Ray camRay){
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
        return objects[minDistanceId]->getColor();
    }
    else{
        Color colorDefault;
        return colorDefault;
    }
}


unsigned char* Scene::Render(unsigned int imgWidth, unsigned int imgHeight, Vector3d rayTracerOrigin){
    unsigned char* buffer = new unsigned char[imgWidth * imgHeight * 3];
    for(int w=0; w<imgWidth; w++){
        for(int h=0; h<imgHeight; h++){
            Vector3d bufferPoint(w - (int)(imgWidth / 2), h - (int)(imgHeight / 2), 0);
            Vector3d rayDir = bufferPoint - rayTracerOrigin;

            Ray camRay(rayTracerOrigin, rayDir);
            Color PixelColor = getPixelColor(camRay);
            buffer[(h * imgWidth + w) * 3 + 0] = PixelColor.b * PixelColor.a;
            buffer[(h * imgWidth + w) * 3 + 1] = PixelColor.g * PixelColor.a;
            buffer[(h * imgWidth + w) * 3 + 2] = PixelColor.r * PixelColor.a;
        }
    }
    return buffer;
}


void Scene::addObject(Object3d* obj){
    objects.push_back(obj);
}
