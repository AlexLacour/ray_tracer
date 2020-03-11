#include "Bmpfile.h"
#include "Scene.h"

using namespace std;


int main(){
    unsigned int width = 1000;
    unsigned int height = 1000;

    unsigned int dimX = (int)(width / 2);
    unsigned int dimY = (int)(height / 2);
    unsigned int dimZ = (int)(height / 2);

    Scene sceneTP(dimX, dimY, dimZ);

    Vector3d sphereCenter1(0.85, 0, -20);
    Color sphereColor1(1, 0, 0);
    Sphere sphereToAdd1(sphereCenter1, 0.2, sphereColor1, 1, 10, 1);
    sceneTP.addObject(&sphereToAdd1);

    Vector3d sphereCenter2(0, 0.85, -20);
    Color sphereColor2(0, 1, 0);
    Sphere sphereToAdd2(sphereCenter2, 0.2, sphereColor2, 1, 10, 1);
    sceneTP.addObject(&sphereToAdd2);

    // Earth Sphere
    Vector3d sphereCenter3(0, 0, -20);
    Color sphereColor3(0, 0, 1);
    Sphere sphereToAdd3(sphereCenter3, 0.5, sphereColor3, 0.5, 20, 0.5);

    unsigned int earthWidth;
    unsigned int earthHeight;
    unsigned char* earthTexture = BMPFile::LoadBmp("earth.bmp", earthWidth, earthHeight);
    sphereToAdd3.loadTexture(earthTexture, earthWidth, earthHeight);

    sceneTP.addObject(&sphereToAdd3);

    Vector3d lightDirection1(-1, -1, 0);
    DirectionalLight dirLightToAdd1(lightDirection1);
    sceneTP.addLight(&dirLightToAdd1);

    Vector3d lightDirection2(0, 1, 0);
    DirectionalLight dirLightToAdd2(lightDirection2, Color(0.5, 0.5, 0));
    sceneTP.addLight(&dirLightToAdd2);

    Vector3d rayTracerOrigin(0, 0, 10);
    unsigned char* render;

    // Aliasing Tests
    render = sceneTP.Render(width, height, rayTracerOrigin, 1);
    BMPFile::SaveBmp("render_test_sphere_aliasing1.bmp", render, width, height);
    render = sceneTP.Render(width, height, rayTracerOrigin, 2);
    BMPFile::SaveBmp("render_test_sphere_aliasing2.bmp", render, width, height);
    render = sceneTP.Render(width, height, rayTracerOrigin, 4);
    BMPFile::SaveBmp("render_test_sphere_aliasing4.bmp", render, width, height);
    render = sceneTP.Render(width, height, rayTracerOrigin, 6);
    BMPFile::SaveBmp("render_test_sphere_aliasing6.bmp", render, width, height);
    render = sceneTP.Render(width, height, rayTracerOrigin, 8);
    BMPFile::SaveBmp("render_test_sphere_aliasing8.bmp", render, width, height);
    
    return 0;
}
