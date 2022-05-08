#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct {
	int width;
	int height;
	unsigned char *imageData;
	unsigned char *gx;
	unsigned char *gy;

} PGM;


void padding(PGM* image) {
	for (int i = 0; i < image->width; i++) {
		image->imageData[i] = 0;
		image->imageData[(image->height - 1) * image->width + i] = 0;
	}
	
	for (int i = 0; i < image->height; i++) {
		image->imageData[i * image->width] = 0;
		image->imageData[(i + 1) * image->width - 1] = 0;
	} 
}

int convolution(PGM* image, int kernel[3][3], int row, int col) {
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			// printf("convolution\n");
			sum += image->imageData[(i + row) * image->width + j + col] * kernel[i][j];
		}
	}
	return sum;
}

void sobel_edge_detector(PGM* image, PGM* out_image) {
	int mx[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};
	int my[3][3] = {
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};
	
	for (int i = 1; i < image->height - 2; i++) {
		for (int j = 1; j < image->width - 2; j++) {
			int gx = convolution(image, mx, i, j);
			int gy = convolution(image, my, i, j);
			// printf("CHECK FOR I = %d J = %d\n", i, j);
			out_image->imageData[i * image->width + j] = sqrt(gx * gx + gy * gy);
		}
	}
}

void min_max_normalization(PGM* image, int* matrix) {
	int min = 1000000, max = 0;
	
	for(int i = 0; i < image->height; i++) {
		for(int j = 0; j < image->width; j++) {
			int index = i * image->width + j;
			if (matrix[index] < min) {
				min = matrix[index];
			}
			else if (matrix[index] > max) {
				max = matrix[index];
			}
		}
	}
	
	for(int i = 0; i < image->height; i++) {
		for(int j = 0; j < image->width; j++) {
			int index = i * image->width + j;
			double ratio = (double) (matrix[index] - min) / (max - min);
			matrix[index] = ratio * 255;
		}
	} 
}

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
	unsigned char* odata = calloc(InputWidth * InputHeight, sizeof(unsigned char));

	PGM image;
	PGM out_image;
	image.width = InputWidth;
	image.height = InputHeight;
	out_image.width = InputWidth;
	out_image.height = InputHeight;
	image.imageData = calloc(InputWidth * InputHeight, sizeof(unsigned char));
	out_image.imageData = calloc(InputWidth * InputHeight, sizeof(unsigned char));

	for (int i = 0; i < InputWidth * InputHeight * n; i += 4) {
		image.imageData[i / 4] = (pixel[i] * 11 + pixel[i + 1] * 16 + 5 * pixel[i + 2]) / 32;	
		out_image.imageData[i / 4] = (pixel[i] * 11 + pixel[i + 1] * 16 + 5 * pixel[i + 2]) / 32;	
	}


	padding(&image);
	sobel_edge_detector(&image, &out_image);	
	// min_max_normalization(&out_image, out_image.imageData);


	char *outputPath = "output.png";
	char *outputPathSobel = "outputSobel.png";
	stbi_write_png(outputPath, InputWidth, InputHeight, 1, image.imageData, 0);
	stbi_write_png(outputPathSobel, InputWidth, InputHeight, 1, out_image.imageData, 0);

	stbi_image_free(idata);
	stbi_image_free(image.imageData);
	stbi_image_free(out_image.imageData);
	
	return 0;
}
