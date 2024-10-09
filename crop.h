
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "histogram.h"

void CROP(image **img)
{
	// verific daca am imagine incarcata in memorie
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	image imgcropped;
	int rows = (*img)->y2 - (*img)->y1;
	int columns = (*img)->x2 - (*img)->x1;

	// daca e de tipul P1, P2, P4 sau P5
	if (strcmp((*img)->type, "P1") == 0 || strcmp((*img)->type, "P2") == 0 ||
		strcmp((*img)->type, "P4") == 0 || strcmp((*img)->type, "P5") == 0) {
		// aloc memorie pentru matricea auxiliara
		imgcropped.photo = alloc_matrix_int(rows, columns);

		// parcurg matricea si retin in imgcropped selectia facuta
		for (int i = (*img)->y1; i < (*img)->y2; i++) {
			for (int j = (*img)->x1; j < (*img)->x2; j++)
				imgcropped.photo[i - (*img)->y1][j - (*img)->x1] =
					((*img)->photo)[i][j];
		}
		// eliberare matrice veche
		free_matrix_int((*img)->photo, (*img)->rows);
		// aloc memorie cata tb si pun fiecare termen la locul lui
		(*img)->photo = alloc_matrix_int(rows, columns);
		// inlocuiesc fiecare termen in parte
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				(*img)->photo[i][j] = imgcropped.photo[i][j];
		}
		// eliberez memoria de la imgcropped
		free_matrix_int(imgcropped.photo, rows);
	} else {
		// daca e de tipul P3 sau P6
		// aloc memorie pentru matricea auxiliara
		imgcropped.photorgb = alloc_matrix_pixel(rows, columns);

		// parcurg matricea si retin in imgcropped selectia facuta
		for (int i = (*img)->y1; i < (*img)->y2; i++) {
			for (int j = (*img)->x1; j < (*img)->x2; j++) {
				imgcropped.photorgb[i - (*img)->y1][j - (*img)->x1].red =
					(*img)->photorgb[i][j].red;
				imgcropped.photorgb[i - (*img)->y1][j - (*img)->x1].green =
					(*img)->photorgb[i][j].green;
				imgcropped.photorgb[i - (*img)->y1][j - (*img)->x1].blue =
					(*img)->photorgb[i][j].blue;
			}
		}
		// eliberare matrice veche
		free_matrix_pixel((*img)->photorgb, (*img)->rows);
		// aloc memorie cata tb si pun fiecare termen la locul lui
		(*img)->photorgb = alloc_matrix_pixel(rows, columns);
		// inlocuiesc fiecare termen in parte
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				(*img)->photorgb[i][j].red = imgcropped.photorgb[i][j].red;
				(*img)->photorgb[i][j].green = imgcropped.photorgb[i][j].green;
				(*img)->photorgb[i][j].blue = imgcropped.photorgb[i][j].blue;
			}
		}
		// eliberez memoria de la imgcropped
		free_matrix_pixel(imgcropped.photorgb, rows);
	}
	// actualizez noile valori
	(*img)->rows = rows;
	(*img)->columns = columns;
	(*img)->x1 = 0;
	(*img)->x2 = columns;
	(*img)->y1 = 0;
	(*img)->y2 = rows;

    // afisez mesaj
	printf("Image cropped\n");
}
