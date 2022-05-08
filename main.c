#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>


int main() {
	char *inputPath = "hampster.png";
	int InputWidth, InputHeight, n;
	unsigned char *idata = stbi_load(inputPath, &InputWidth, &InputHeight, &n,0);

	if (!idata) {
		printf("ERROR: can't read file \n");
		return 1;
	}

	printf("Loaded image with a width of %dpx,a height of %dpx and %d channels\n",InputWidth,InputHeight,n);
	
	char *pixel = idata;
	unsigned char* odata = malloc(InputWidth * InputHeight * sizeof(unsigned char));
	for (int i = 0; i < InputWidth * InputHeight * n; i += 4) {
		odata[i / 4] = (pixel[i] * 11 + pixel[i + 1] * 16 + 5 * pixel[i + 2]) / 32;	
	}
	
	/*int d=3;
	for(int s=0;s<=InputWidth*InputHeight*n;s++){
		for(int t=s;t<=InputWidth*InputHeight;t++){
			
			if (abs(odata[s]-odata[t])<20)){
				graph[s][t]=abs(odata[s]-odata[t]);
				
}
}
}	*/
char *outputPath = "output.png";
stbi_write_png(outputPath, InputWidth, InputHeight, 1, odata, 0);
stbi_image_free(idata);
stbi_image_free(odata);
return 0;
}
