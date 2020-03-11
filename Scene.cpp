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
        if(distance > 0){
            return objects[minDistanceId];
        }
    }
    return NULL;
}


Color Scene::RayTrace(Ray camRay, int recursiveDepth){
    // Find Nearest Object
    float distance;
    Object3d* nearestObject = getNearestObject(camRay, distance);
    Color pixelColor;
    Color finalColor(0, 0, 0);

    if(nearestObject){
        // Get Object Color
        pixelColor = nearestObject->getColor();
        Vector3d spherePoint = camRay.getOrigin() + (camRay.getDir() * distance);
        Vector3d normalVector = nearestObject->getNormalAt(spherePoint);
        Vector3d toObserver = camRay.getDir() * (-1);
        if(nearestObject->hasTexture()){
            pixelColor = nearestObject->getColorTexture(normalVector) * ((float)1 / (float)255);
        }
        float diffuseLightFactor = 0.0;
        Color diffuseLight(0, 0, 0);

        float specularLightFactor = 0.0;
        Color specularLight(0, 0, 0);

        for(unsigned int lightId=0; lightId<lights.size(); lightId++){
            Vector3d lightDir = lights[lightId]->getDirection();
            Vector3d toLight = (lightDir * (-1));

            spherePoint = camRay.getOrigin() + (camRay.getDir() * distance);
            normalVector = nearestObject->getNormalAt(spherePoint);

            // Diffuse Light : Lambert model
            diffuseLightFactor = std::max(normalVector.dot(toLight), 0.0f);
            diffuseLight = diffuseLight + lights[lightId]->getColor() * diffuseLightFactor;

            // Specular Light : Phong model
            Vector3d reflexionVector = (normalVector * (2 * normalVector.dot(toLight)) - toLight).normalize();
            specularLightFactor = std::pow(std::max(reflexionVector.dot(toObserver), 0.0f), nearestObject->getNs()) * nearestObject->getKs();
            specularLight = specularLight + lights[lightId]->getColor() * specularLightFactor;
        }

        finalColor += pixelColor * diffuseLight;
        finalColor += specularLight;

        Vector3d reflectedRayDir = (normalVector * (2 * normalVector.dot(toObserver)) - toObserver).normalize();
        Ray reflectedRay(spherePoint, reflectedRayDir);

        if(recursiveDepth > 0){
            return (finalColor + RayTrace(reflectedRay, recursiveDepth - 1) * nearestObject->getKr());
        }
    }
    return finalColor;
}


unsigned char* Scene::Render(unsigned int imgWidth, unsigned int imgHeight, Vector3d rayTracerOrigin, int numberRays){
    unsigned char* buffer = new unsigned char[imgWidth * imgHeight * 3];
    for(int w=0; w<imgWidth; w++){
        for(int h=0; h<imgHeight; h++){
            Vector3d bufferPoint((double)(w - (int)(imgWidth / 2)) / (double)imgWidth,
                                 - (double)(h - (int)(imgHeight / 2)) / (double)imgHeight,
                                 0);

            Vector3d bufferPointAlteration;
            Vector3d bufferPointAltered;
            Vector3d rayDir;

            Color PixelColor(0, 0, 0);
            for(unsigned int rayId=0; rayId<numberRays; rayId++){
                bufferPointAlteration = Vector3d((double)(rand() / RAND_MAX),
                                                 (double)(rand() / RAND_MAX),
                                                 0);
                bufferPointAltered = bufferPoint + bufferPointAlteration * ((float)1 / (float)1000);
                rayDir = bufferPointAltered - rayTracerOrigin;
                Ray camRay(rayTracerOrigin, rayDir);

                PixelColor += RayTrace(camRay, 0) * ((float)1 / (float)numberRays);
            }
            PixelColor.cap();

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
