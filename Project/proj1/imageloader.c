/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		return NULL;
	}

	char file_type[3];

	if (fscanf(fp, "%2s", file_type) != 1 || file_type[0] != 'P' || file_type[1] != '3') {
		printf("File is not correct type\n");
		fclose(fp);
		return NULL;
	}

	int col, row, max_value;
	if (fscanf(fp, "%d %d", &col, &row) != 2 || col < 1 || row < 1) {
		fclose(fp);
		return NULL;
	}
	if (fscanf(fp, "%d", &max_value) != 1 || max_value != 255) {
		fclose(fp);
		return NULL;
	}
	Image *img = (Image *) malloc(sizeof(Image));
	if (!img) {
		fclose(fp);
		return NULL;
	}
	img -> cols = col;
	img -> rows = row;
	img -> image = (Color **)malloc(row * sizeof(Color *));
	if (!img -> image) {
		fclose(fp);
		free(img);
		return NULL;
	}
	uint8_t R,G,B;
	for (int r = 0; r < img-> rows; r++) {
		img -> image[r] = (Color *)malloc(col * sizeof(Color));
		if (!img -> image[r]) {
			for (int i = 0; i <= r; i++) {
				free(img -> image[i]);
			}
			free(img -> image);
			free(img);
			fclose(fp);
			return NULL;
		}
		for (int c = 0; c < img-> cols; c++) {
			if (fscanf(fp, "%hhu %hhu %hhu", &R, &G, &B) != 3) {
				for (int i = 0; i <= r; i++) {
					free(img -> image[i]);
				}
				free(img -> image);
				free(img);
				fclose(fp);
				return NULL;
			}
			img -> image [r][c].R = R;
			img -> image [r][c].G = G;
			img -> image [r][c].B = B;
		}
	}
	fclose(fp);

	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image) {
	printf("P3\n");
	printf("%d %d\n255\n", image-> cols, image-> rows);
	for (int r = 0; r < image-> rows; r++) {
		for (int c = 0; c < image-> cols; c++) {
			printf("%3hhu %3hhu %3hhu", image -> image[r][c].R, image -> image[r][c].G, image -> image[r][c].B);
			if (c + 1 < image-> cols) {
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image) {
	for (int r = 0; r < image-> rows; r++) {
		free(image-> image [r]);
	};
	free(image-> image);
	free(image);
}