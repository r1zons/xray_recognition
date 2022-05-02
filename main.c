#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	char* inputPath ="hampster.png";
	int iw,ih,n;
	unsigned char * idata = stbi_load(inputPath,&iw,&ih,&n,0);
	if (idata == NULL){
		printf("ERROR: can't read file \n");
		return 1;
}
/*	char *pixel =idata;
	unsigned char* odata(unsigned char *) malloc(iw*ih*n);
	int d=3;
	for(int s=-d;s<=d;s++){
		for(int t=-d;t<=d;t++){
			p1=p(i+s,j+t);
			if (abs p1[0]-p[0])<20){
				
}
}
}
char *outputPath="output.png";
stbi_write_png(outputPath,ow,oh,n,odata,0);*/
stbi_image_free(idata);
//stbi_image_free(odata);
printf("Loaded image with a width of %dpx,a height of %dpx and %d channels\n",iw,ih,n);
return 0;
}
