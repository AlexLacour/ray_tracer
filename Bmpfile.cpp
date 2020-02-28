#include "Bmpfile.h"
#include <cstdio>
#include <cstring>

void BMPFile::SaveBmp(std::string fileName, unsigned char *imageBuffer, unsigned int w, unsigned int h)
{
	int filesize = 54 + 3 * w * h;  //w is your image width, h is image height, both int

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	
	FILE *f = fopen(fileName.c_str(),"wb");
		fwrite(bmpfileheader,1,14,f);
		fwrite(bmpinfoheader,1,40,f);
	for(unsigned int i=0; i<h; i++)
	{
		fwrite(imageBuffer+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
}


unsigned char *BMPFile::LoadBmp(std::string fileName, unsigned int &width, unsigned int &height, bool flipY) {
	printf("Reading image %s\n", fileName.c_str());

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file;
	file = fopen(fileName.c_str(), "rb");
	if (!file) { printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", fileName.c_str()); getchar(); return 0; }

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	// https://github.com/mortennobel/OpenGL_3_2_Utils/blob/master/src/TextureLoader.cpp
	if (flipY) {
		// swap y-axis
		unsigned char * tmpBuffer = new unsigned char[width * 3];
		int size = width * 3;
		for (unsigned int i = 0; i<height / 2; i++) {
			// copy row i to tmp
			memcpy(tmpBuffer, data + width * 3 * i, size);
			// copy row h-i-1 to i
			memcpy(data + width * 3 * i, data + width * 3 * (height - i - 1), size);
			// copy tmp to row h-i-1
			memcpy(data + width * 3 * (height - i - 1), tmpBuffer, size);
		}
		delete[] tmpBuffer;
	}

	return data;
}
