#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>


// typedef struct {
// 	int width;
// 	int height;
// 	unsigned char *imageData;
// } pgm;


// void padding(pgm* image) {
// 	for (int i = 0; i < image->width; i++) {
// 		image->imageData[i] = 0;
// 		image->imageData[image->height] = 0;
// 	}
	
// 	for (int i = 0; i < image->height; i++) {
// 		image->imageData[i][0] = 0;
// 		image->imageData[i][(image->width - 1)] = 0;
// 	} 
// }



int main() {
	char *inputPath = "hampster.png";
	int InputWidth, InputHeight, n;
	unsigned char *idata = stbi_load(inputPath, &InputWidth, &InputHeight, &n, 0);

	if (!idata) {
		printf("ERROR: can't read file \n");
		return 1;
	}

	printf("Loaded image with a width of %dpx,a height of %dpx and %d channels\n",InputWidth,InputHeight,n);
	
	char *pixel = idata;
	unsigned char* odata = malloc(InputWidth * InputHeight * sizeof(unsigned char));
	unsigned char* odataSobel = malloc(InputWidth * InputHeight * sizeof(unsigned char));

	for (int i = 0; i < InputWidth * InputHeight * n; i += 4) {
		odata[i / 4] = (pixel[i] * 11 + pixel[i + 1] * 16 + 5 * pixel[i + 2]) / 32;	
		odataSobel[i / 4] = (pixel[i] * 11 + pixel[i + 1] * 16 + 5 * pixel[i + 2]) / 32;	

	}
	
	








	char *outputPath = "output.png";
	char *outputPathSobel = "outputSobel.png";
	stbi_write_png(outputPath, InputWidth, InputHeight, 1, odata, 0);
	stbi_write_png(outputPathSobel, InputWidth, InputHeight, 1, odataSobel, 0);
	stbi_image_free(idata);
	stbi_image_free(odata);
	stbi_image_free(odataSobel);
	return 0;
}
