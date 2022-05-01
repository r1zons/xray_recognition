#include "stb_image.h"
#include "stb_image_write.h"
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>
#define p(i,j) idata[(i)+(j)*iw]
int main(){
	char* inputPath = "/Pictures/input.png";
	int iw,ih,n;
	unsigned char * idata = stbi_load(inputPath,&iw,&ih,&n,0);
	if (idata == NULL){
		printf("ERROR: can't read file %s/n",inputPath);
		return 1;
}
	char *pixel =idata;
	pixel=pixel +n;
	char*pixel=p(i,j);
	unsigned char* odata(unsigned char *) malloc(iw*ih*n)
	int d=3;
	for(int s=-d;s<=d;s++){
		for(int t=-d;t<=d;t++){
			p1=p(i+s,j+t);
			if (abs p1[0]-p[0])<20){
				...
}
}
}
char *outputPath="~/Pictures/output.png";
stbi_write_png(outputPath,ow,oh,n,odata,0);
stbi_image_free(idata);
stbi_image_free(odata);
return 0;
}
