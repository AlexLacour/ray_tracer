#include "Bmpfile.h"
#include "Scene.h"

using namespace std;


int main(){
    unsigned int width = 480;
    unsigned int height = 480;

    unsigned int dimX = (int)(width / 2);
    unsigned int dimY = (int)(height / 2);
    unsigned int dimZ = (int)(height / 2);

    Scene testScene(dimX, dimY, dimZ);

    Vector3d sphereCenter1(0, 0, -20);
    Color sphereColor(0, 255, 255);
    Sphere sphereToAdd(sphereCenter1, 20, sphereColor);

    Vector3d sphereCenter2(10, 20, -30);
    Color sphereColor2(255, 0, 0);
    Sphere sphereToAdd2(sphereCenter2, 20, sphereColor2);

    testScene.addObject(&sphereToAdd);
    testScene.addObject(&sphereToAdd2);

    Vector3d rayTracerOrigin(0, 0, 10);
    unsigned char* render = testScene.Render(width, height, rayTracerOrigin);
    BMPFile::SaveBmp("render_test_sphere.bmp", render, width, height);
    return 0;
}
