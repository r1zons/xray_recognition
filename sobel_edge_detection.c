#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int isspace(int argument);

typedef struct {
	char version[3]; 
	int width;
	int height;
	int maxGrayLevel;
	int **imageData;
	int **gx;
	int **gy;
} pgm;


void padding(pgm* image) {
	int i;
	for (i = 0; i < image->width; i++) {
		image->imageData[0][i] = 0;
		image->imageData[image->height - 1][i] = 0;
	}
	
	for (i = 0; i < image->height; i++) {
		image->imageData[i][0] = 0;
		image->imageData[i][image->width - 1] = 0;
	} 
}

int convolution(pgm* image, int kernel[3][3], int row, int col) {
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sum += image->imageData[i + row][j + col] * kernel[i][j];
		}
	}
	return sum;
}

void sobel_edge_detector(pgm* image, pgm* out_image) {
	int i, j, gx, gy;
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
	
	for (i = 1; i < image->height - 2; i++) {
		for (j = 1; j < image->width - 2; j++) {
			gx = convolution(image, mx, i, j);
			gy = convolution(image, my, i, j);
			out_image->imageData[i][j] = sqrt(gx*gx + gy*gy);
			out_image->gx[i][j] = gx;
			out_image->gy[i][j] = gy;
		}
	}
	
}

void min_max_normalization(pgm* image, int** matrix) {
	int min = 1000000, max = 0, i, j;
	
	for(i = 0; i < image->height; i++) {
		for(j = 0; j < image->width; j++) {
			if (matrix[i][j] < min) {
				min = matrix[i][j];
			}
			else if (matrix[i][j] > max) {
				max = matrix[i][j];
			}
		}
	}
	
	for(i = 0; i < image->height; i++) {
		for(j = 0; j < image->width; j++) {
			double ratio = (double) (matrix[i][j] - min) / (max - min);
			matrix[i][j] = ratio * 255;
		}
	} 
}


int main(int argc, char **argv)
{
	pgm image, out_image;
	char dir[200];
	printf("Enter the file name: ");
	scanf("%s", dir);
	
	read_pgm_file(dir, &image);
	padding(&image);
	init_out_image(&out_image, image);
	sobel_edge_detector(&image, &out_image);	
	
	min_max_normalization(&out_image, out_image.imageData);
	min_max_normalization(&out_image, out_image.gx);
	min_max_normalization(&out_image, out_image.gy);

	write_pgm_file(&out_image, dir, out_image.imageData, ".G.pgm");
	printf("\nGradient saved: %s \n", dir);
	write_pgm_file(&out_image, dir, out_image.gx, ".GX.pgm");
	printf("Gradient X saved: %s \n", dir);
	write_pgm_file(&out_image, dir, out_image.gy, ".GY.pgm");
	printf("Gradient Y saved: %s \n", dir);

	free(image.imageData);
	free(out_image.imageData);
	free(out_image.gx);
	free(out_image.gy);
	
	return 0;
}
