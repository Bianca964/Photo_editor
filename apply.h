// Farcasanu Bianca Ioana 313CAb 2023-2024

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "crop.h"

int clamp_int(int n, int min, int max)
{
	if (n < min)
		return min;
	if (n > max)
		return max;
	return n;
}

void APPLY_PARAMETER(image ***img, double kernel[][3])
{
	// usurez notatiile
	int x1 = (**img)->x1;
	int y1 = (**img)->y1;
	int x2 = (**img)->x2;
	int y2 = (**img)->y2;
	int rows = (**img)->rows;
	int columns = (**img)->columns;

	// matricea auxiliara
	pixel **new_image = alloc_matrix_pixel(rows, columns);

	// parcurg selectia
	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			// daca sunt margini, nu le modific
			if (i == 0 || i == (rows - 1) || j == 0 || j == (columns - 1)) {
				new_image[i][j].red = (**img)->photorgb[i][j].red;
				new_image[i][j].green = (**img)->photorgb[i][j].green;
				new_image[i][j].blue = (**img)->photorgb[i][j].blue;
				continue;
			}

			// daca nu sunt margini, le modific
			new_image[i][j].red =
				round(((**img)->photorgb[i - 1][j - 1].red * kernel[0][0])
				+ ((**img)->photorgb[i - 1][j].red * kernel[0][1]) +
				((**img)->photorgb[i - 1][j + 1].red * kernel[0][2]) +
				((**img)->photorgb[i][j - 1].red * kernel[1][0]) +
				((**img)->photorgb[i][j].red * kernel[1][1]) +
				((**img)->photorgb[i][j + 1].red * kernel[1][2]) +
				((**img)->photorgb[i + 1][j - 1].red * kernel[2][0]) +
				((**img)->photorgb[i + 1][j].red * kernel[2][1]) +
				((**img)->photorgb[i + 1][j + 1].red * kernel[2][2]));
			new_image[i][j].green =
				round(((**img)->photorgb[i - 1][j - 1].green * kernel[0][0])
				+ ((**img)->photorgb[i - 1][j].green * kernel[0][1]) +
				((**img)->photorgb[i - 1][j + 1].green * kernel[0][2]) +
				((**img)->photorgb[i][j - 1].green * kernel[1][0]) +
				((**img)->photorgb[i][j].green * kernel[1][1]) +
				((**img)->photorgb[i][j + 1].green * kernel[1][2]) +
				((**img)->photorgb[i + 1][j - 1].green * kernel[2][0]) +
				((**img)->photorgb[i + 1][j].green * kernel[2][1]) +
				((**img)->photorgb[i + 1][j + 1].green * kernel[2][2]));
			new_image[i][j].blue =
				round(((**img)->photorgb[i - 1][j - 1].blue * kernel[0][0])
				+ ((**img)->photorgb[i - 1][j].blue * kernel[0][1]) +
				((**img)->photorgb[i - 1][j + 1].blue * kernel[0][2]) +
				((**img)->photorgb[i][j - 1].blue * kernel[1][0]) +
				((**img)->photorgb[i][j].blue * kernel[1][1]) +
				((**img)->photorgb[i][j + 1].blue * kernel[1][2]) +
				((**img)->photorgb[i + 1][j - 1].blue * kernel[2][0]) +
				((**img)->photorgb[i + 1][j].blue * kernel[2][1]) +
				((**img)->photorgb[i + 1][j + 1].blue * kernel[2][2]));

			// limitez cu clamp
			new_image[i][j].red = clamp_int(new_image[i][j].red, 0, 255);
			new_image[i][j].green = clamp_int(new_image[i][j].green, 0, 255);
			new_image[i][j].blue = clamp_int(new_image[i][j].blue, 0, 255);
		}
	}

	// inlocuiesc toti termenii matricei vechi cu cei din new_image
	for (int i = y1; i < y2; i++) {
		for (int j = x1; j < x2; j++) {
			(**img)->photorgb[i][j].red = new_image[i][j].red;
			(**img)->photorgb[i][j].green = new_image[i][j].green;
			(**img)->photorgb[i][j].blue = new_image[i][j].blue;
		}
	}

	// eliberez matricea auxiliara
	free_matrix_pixel(new_image, rows);
}

void APPLY(image **img, char *parametru)
{
	// verific daca am imagine incarcata in memorie
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	// verific daca parametrul este valid
	if (strcmp(parametru, "EDGE") != 0 && strcmp(parametru, "SHARPEN") != 0 &&
		strcmp(parametru, "BLUR") != 0 &&
		strcmp(parametru, "GAUSSIAN_BLUR") != 0) {
		printf("APPLY parameter invalid\n");
		return;
	}

	// daca e de tipul P2 sau P5 afisez eroare
	if (strcmp((*img)->type, "P2") == 0 || strcmp((*img)->type, "P5") == 0) {
		printf("Easy,Charlie Chaplin\n");
		return;
	}

	// daca e de tipul P3 sau P6 aplic APPLY
	if (strcmp((*img)->type, "P3") == 0 || strcmp((*img)->type, "P6") == 0) {
		if (strcmp(parametru, "EDGE") == 0) {
			// initializez cu matricea din kernel aferenta lui EDGE
			double kernel[3][3] = {
				{-1, -1, -1},
				{-1, 8, -1},
				{-1, -1, -1}
			};

			APPLY_PARAMETER(&img, kernel);
		} else if (strcmp(parametru, "SHARPEN") == 0) {
			// initializez cu matricea din kernel aferenta lui SHARPEN
			double kernel[3][3] = {
				{0, -1, 0},
				{-1, 5, -1},
				{0, -1, 0}
			};

			APPLY_PARAMETER(&img, kernel);
		} else if (strcmp(parametru, "BLUR") == 0) {
			// initializez cu matricea din kernel aferenta lui BLUR
			double kernel[3][3] = {
				{1. / 9, 1. / 9, 1. / 9},
				{1. / 9, 1. / 9, 1. / 9},
				{1. / 9, 1. / 9, 1. / 9}
			};

			APPLY_PARAMETER(&img, kernel);
		} else if (strcmp(parametru, "GAUSSIAN_BLUR") == 0) {
			// initializez cu matricea din kernel aferenta lui GAUSSIAN_BLUR
			double kernel[3][3] = {
				{1. / 16, 1. / 8, 1. / 16},
				{1. / 8, 1. / 4, 1. / 8},
				{1. / 16, 1. / 8, 1. / 16}
			};

			APPLY_PARAMETER(&img, kernel);
		}

		// afisez mesaj dupa ce termin de modificat imaginea
		printf("APPLY %s done\n", parametru);
	}
}
