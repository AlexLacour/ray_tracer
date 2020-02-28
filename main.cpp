#include "Bmpfile.h"
#include "Scene.h"

using namespace std;


int main(){
    unsigned int width = 800;
    unsigned int height = 800;

    unsigned int dimX = (int)(width / 2);
    unsigned int dimY = (int)(height / 2);
    unsigned int dimZ = (int)(height / 2);

    Scene testScene(dimX, dimY, dimZ);

    Vector3d sphereCenter1(0, 0, -20);
    Color sphereColor(1, 0, 0);
    Sphere sphereToAdd(sphereCenter1, 0.5, sphereColor);
    testScene.addObject(&sphereToAdd);

    Vector3d sphereCenter2(-0.4, 0, -20);
    Color sphereColor2(0, 0, 1);
    Sphere sphereToAdd2(sphereCenter2, 0.7, sphereColor2);
    testScene.addObject(&sphereToAdd2);

    Vector3d lightDirection(1, 1, 0);
    DirectionalLight dirLightToAdd(lightDirection);
    testScene.addLight(&dirLightToAdd);

    Vector3d rayTracerOrigin(0, 0, 10);
    unsigned char* render = testScene.Render(width, height, rayTracerOrigin);
    BMPFile::SaveBmp("render_test_sphere.bmp", render, width, height);
    return 0;
}
