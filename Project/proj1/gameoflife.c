/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
int8_t dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int8_t dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int ring (int n, int m) {
	return (n + m) % m;
}

Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color *next_state = malloc(sizeof(Color));
	*next_state = image -> image[row][col];
	int8_t neighbour_alive_R = 0, neighbour_alive_G = 0, neighbour_alive_B = 0;
	int isalive_R, isalive_G, isalive_B;
	int indexR, indexG, indexB;

	isalive_R = image ->image[row][col].R == 255;
	isalive_G = image -> image[row][col].G == 255;
	isalive_B = image -> image[row][col].B == 255;

	for (int i = 0; i < 8; i++) {
		int new_row = ring(row + dx[i], image -> rows) , new_col = ring(col + dy[i], image -> cols);
		if (image -> image[new_row][new_col].R == 255) {
			neighbour_alive_R += 1;
		}
		if (image -> image[new_row][new_col].G == 255) {
			neighbour_alive_G += 1;
		}
		if (image -> image[new_row][new_col].B == 255) {
			neighbour_alive_B += 1;
		}
	}

	indexR = isalive_R * 9 + neighbour_alive_R;
	indexG = isalive_G * 9 + neighbour_alive_G;
	indexB = isalive_B * 9 + neighbour_alive_B;

	if (rule & (1 << indexR)) {
		next_state -> R = 255;
	} else {
		next_state -> R = 0;
	}
	if (rule & (1 << indexG)) {
		next_state -> G = 255;
	} else {
		next_state -> G = 0;
	}
	if (rule & (1 << indexB)) {
		next_state -> B = 255;
	} else {
		next_state -> B = 0;
	}

	return next_state;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule) {
	Image *new_image = (Image*)malloc(sizeof(Image));
	*new_image = *image;
	new_image ->cols = image->cols;
	new_image ->rows = image->rows;
	new_image ->image = (Color **)malloc(sizeof(Color*) * new_image -> rows);
	for (int r = 0; r < new_image -> rows; r++) {
		new_image -> image[r] = malloc(sizeof(Color) * new_image -> cols);
		for (int c = 0; c < new_image -> cols; c++) {
			Color *color = evaluateOneCell(image, r, c, rule);
			new_image -> image[r][c] = *color;
			free(color);
		}
	}
	return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with maximum value 255.\nrule is a hex number beginning with 0x; Life is 0x1808.");
		return 1;
	}
	char *filename = argv[1];
	Image *image = readData(filename);
	if (!image) {
		printf("Error reading image\n");
		return 0;
	}
	uint16_t rule = strtol(argv[2], NULL, 16);
	Image * next_image = life(image, rule);
	writeData(next_image);
	freeImage(image);
	freeImage(next_image);
	return 0;
}
