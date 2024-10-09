// Farcasanu Bianca Ioana 313CAb 2023-2024

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "equalize.h"

// salveaza o imagine grayscale sau alb-negru in format text
void save_img_int_ascii(image *img, FILE *file)
{
	int rows = img->rows;
	int columns = img->columns;

	// scriu in fisier tipul corespunzator, liniile si coloanele
	if (strcmp(img->type, "P1") == 0 || strcmp(img->type, "P4") == 0) {
		fprintf(file, "P1\n");
		fprintf(file, "%d %d\n", columns, rows);
	} else {
		fprintf(file, "P2\n");
		fprintf(file, "%d %d\n", columns, rows);
		fprintf(file, "255\n");
	}

	// afisez imaginea in fisier
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			fprintf(file, "%d ", img->photo[i][j]);
		fprintf(file, "\n");
	}
}

// salveaza o imagine color in format text
void save_img_rgb_ascii(pixel **imgrgb, int rows, int columns, FILE *file)
{
	// scriu in fisier tipul corespunzator, liniile, coloanele si valoarea ascii
	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", columns, rows);
	fprintf(file, "255\n");

	// afisez imaginea in fisier
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			fprintf(file, "%d %d %d ", imgrgb[i][j].red, imgrgb[i][j].green,
					imgrgb[i][j].blue);
		fprintf(file, "\n");
	}
}

// salveaza o imagine grayscale sau alb-negru in format binar
void save_img_int_binary(image *img, FILE *file)
{
	int rows = img->rows;
	int columns = img->columns;

	// afisez matricea in fisier
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			fwrite(&img->photo[i][j], sizeof(unsigned char), 1, file);
	}
}

// salveaza o imagine color in format binar
void save_img_rgb_binary(pixel **imgrgb, int rows, int columns, FILE *file)
{
	// afisez matricea in fisier pixel cu pixel
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			fwrite(&imgrgb[i][j].red, sizeof(unsigned char), 1, file);
			fwrite(&imgrgb[i][j].green, sizeof(unsigned char), 1, file);
			fwrite(&imgrgb[i][j].blue, sizeof(unsigned char), 1, file);
		}
	}
}

void SAVE(image **img, char **output, char *ascii)
{
	// verific daca am imagine incarcata in memorie
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	// deschid initial in format "w" pt a scrie tipul, liniile, coloanele
	FILE *file = fopen(*output, "w");
	if (!file) {
		printf("Failed to open %s\n", *output);
		return;
	}

	// salvare in format ascii
	if (ascii) {
		if (strcmp((*img)->type, "P1") == 0 ||
			strcmp((*img)->type, "P2") == 0 ||
			strcmp((*img)->type, "P4") == 0 || strcmp((*img)->type, "P5") == 0)
			save_img_int_ascii(*img, file);
		else if (strcmp((*img)->type, "P3") == 0 ||
				 strcmp((*img)->type, "P6") == 0)
			save_img_rgb_ascii((*img)->photorgb, (*img)->rows,
							   (*img)->columns, file);
	// salvare in format binar
	} else {
		if (strcmp((*img)->type, "P1") == 0 ||
			strcmp((*img)->type, "P2") == 0 ||
			strcmp((*img)->type, "P4") == 0 ||
			strcmp((*img)->type, "P5") == 0) {
			// daca e de tip P1 sau P4
			if (strcmp((*img)->type, "P1") == 0 ||
				strcmp((*img)->type, "P4") == 0) {
				fprintf(file, "P4\n");
				fprintf(file, "%d %d\n", (*img)->columns, (*img)->rows);
			} else {
				// daca e de tipul P2 sau P5
				fprintf(file, "P5\n");
				fprintf(file, "%d %d\n", (*img)->columns, (*img)->rows);
				fprintf(file, "255\n");
			}

			// inchid fisierul
			fclose(file);

			// il deschid in mod binar
			file = fopen(*output, "ab");

			// salvez restul (imaginea) in format binar
			save_img_int_binary(*img, file);

		// daca e de tipul P3 sau P6 (pixel)
		} else if (strcmp((*img)->type, "P3") == 0 ||
				   strcmp((*img)->type, "P6") == 0) {
			// afisez primele 3 randuri ascii
			fprintf(file, "P6\n");
			fprintf(file, "%d %d\n", (*img)->columns, (*img)->rows);
			fprintf(file, "255\n");

			// inchid fisierul deschis cu "w"
			fclose(file);

			// il deschid in mod binar
			file = fopen(*output, "ab");

			// salvez restul (imaginea) in format binar
			save_img_rgb_binary((*img)->photorgb, (*img)->rows,
								(*img)->columns, file);
		}
	}

	// inchid fisierul definitiv
	fclose(file);

	// afisez mesaj dupa ce am facut toate operatiile
	printf("Saved %s\n", *output);
}

void EXIT(image **img, char **input)
{
	// verific daca am imagine incarcata in memorie
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		free(*img);
		free(*input);
		return;
	}

	// daca matricea folosita e P1,P2,P4 sau P5 o eliberez
	if ((*img)->photo)
		free_matrix_int((*img)->photo, (*img)->rows);

	// daca matricea folosita e P3 sau P6 o eliberez
	if ((*img)->photorgb)
		free_matrix_pixel((*img)->photorgb, (*img)->rows);

    // eliberez restul variabilelor
	free(*img);
	free(*input);
}
