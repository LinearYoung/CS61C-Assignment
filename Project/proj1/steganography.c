/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	Color *color = malloc(sizeof(Color));
	if (!color) {
		return NULL;
	}
	uint8_t value = (image-> image[row][col].B & 1) ? 255 : 0;
	color -> R = value;
	color -> G = value;
	color -> B = value;
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image* steganography = (Image *)malloc(sizeof(Image));
	if (!steganography) {
		return NULL;
	}
	steganography -> rows = image-> rows;
	steganography -> cols = image-> cols;

	steganography -> image = (Color **)malloc(steganography -> rows * sizeof(Color *));
	if (steganography -> image == NULL) {
		return NULL;
	}

	for (int r = 0; r < steganography-> rows; r++) {
		steganography -> image[r] = (Color *)malloc(steganography -> cols * sizeof(Color));
		for (int c = 0; c < steganography-> cols; c++) {
			Color *color = evaluateOnePixel(image, r, c);
			steganography -> image[r][c] = *color;
			free(color);
		}
	}
	return steganography;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	if (argc != 2) {
		return -1;
	}

	char *filename = argv[1];
	Image *image = readData(filename);
	if (image == NULL) {
		return -1;
	}
	Image *stegano = steganography(image);
	if (stegano == NULL) {
		return -1;
	}
	writeData(stegano);
	freeImage(stegano);
	freeImage(image);

	return 0;
}
