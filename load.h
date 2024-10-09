
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "memory_allocation.h"

void read_p1_ascii(image ***matrix, FILE *file)
{
	fscanf(file, "%d", &(**matrix)->columns);
	fscanf(file, "%d", &(**matrix)->rows);

	// aloc memorie pentru matricea ce va stoca imaginea
	(**matrix)->photo = alloc_matrix_int((**matrix)->rows,
										 (**matrix)->columns);

	// citesc matricea
	read_matrix_int(&((**matrix)->photo), (**matrix)->rows,
					(**matrix)->columns, file);
}

void read_p2_ascii(image ***matrix, FILE *file)
{
	int ascii;
	fscanf(file, "%d", &(**matrix)->columns);
	fscanf(file, "%d", &(**matrix)->rows);
	fscanf(file, "%d", &ascii);

	// aloc memorie pentru matricea ce va stoca imaginea
	(**matrix)->photo = alloc_matrix_int((**matrix)->rows,
										 (**matrix)->columns);

	// citesc matricea
	read_matrix_int(&((**matrix)->photo), (**matrix)->rows,
					(**matrix)->columns, file);
}

void read_p3_ascii(image ***matrix, FILE *file)
{
	int ascii;
	fscanf(file, "%d", &(**matrix)->columns);
	fscanf(file, "%d", &(**matrix)->rows);
	fscanf(file, "%d", &ascii);

	// aloc memorie pentru matricea ce va stoca imaginea
	(**matrix)->photorgb = alloc_matrix_pixel((**matrix)->rows,
											  (**matrix)->columns);

	// citesc matricea
	read_matrix_pixel((**matrix)->photorgb, (**matrix)->rows,
					  (**matrix)->columns, file);
}

void read_p4_binary(image ***matrix, FILE *file, const char *filename)
{
	fscanf(file, "%d", &(**matrix)->columns);
	fscanf(file, "%d", &(**matrix)->rows);

	fclose(file);
	file = fopen(filename, "rb");

	// mut cursorul pe randul 3 pt a citi matricea binar
	// numarul liniei pe care vreau sa ajung
	int nrlinie = 3;
	// variabila pentru a numara liniile
	int rows = 1;

	// parcurge fisierul pana la linia 3
	while (rows < nrlinie) {
		char c = fgetc(file);
		// fiind un singur caracter il pot compara cu "=="
		if (c == '\n')
			// daca gasesc un caracter newline, trec la urmatoarea linie
			rows++;
	}
	// acum sunt la inceputul liniei 3

	// aloc memorie
	(**matrix)->photo = alloc_matrix_int((**matrix)->rows,
										 (**matrix)->columns);

	// citesc matricea
	for (int i = 0; i < (**matrix)->rows; i++) {
		for (int j = 0; j < (**matrix)->columns; j++) {
			unsigned char color;
			fread(&color, sizeof(unsigned char), 1, file);
			((**matrix)->photo)[i][j] = (int)(color);
		}
	}
}

void read_p5_binary(image ***matrix, FILE *file, const char *filename)
{
	int ascii;
	fscanf(file, "%d", &(**matrix)->columns);
	fscanf(file, "%d", &(**matrix)->rows);
	fscanf(file, "%d", &ascii);

	fclose(file);
	FILE *file2 = fopen(filename, "rb");

	// mut cursorul pe randul 4 pt a citi matricea binar
	// numarul liniei pe care vreau sa ajung
	int nrlinie = 4;
	// variabila pentru a numara liniile
	int rows = 1;

	// parcurge fisierul pana la linia 4
	while (rows < nrlinie) {
		char c = fgetc(file2);
		// fiind un sigur caracter il pot compara cu "=="
		if (c == '\n')
			// daca gasesc un caracter newline, trec la urmatoarea linie
			rows++;
	}
	// acum sunt la inceputul liniei 4

	// aloc memorie
	(**matrix)->photo = alloc_matrix_int((**matrix)->rows,
										 (**matrix)->columns);

	// citesc matricea
	for (int i = 0; i < (**matrix)->rows; i++) {
		for (int j = 0; j < (**matrix)->columns; j++) {
			unsigned char color;
			fread(&color, sizeof(unsigned char), 1, file2);
			((**matrix)->photo)[i][j] = (int)(color);
		}
	}

	//inchid fisierul
	fclose(file2);
}

void read_p6_binary(image ***matrix, FILE *file, const char *filename)
{
	int ascii;
	fscanf(file, "%d", &(**matrix)->columns);
	fscanf(file, "%d", &(**matrix)->rows);
	fscanf(file, "%d", &ascii);

	fclose(file);
	FILE *file2 = fopen(filename, "rb");

	// mut cursorul pe randul 4 pt a citi matricea binar
	// numarul liniei pe care vreau sa ajung
	int nrlinie = 4;
	// variabila pentru a numara liniile
	int rows = 1;

	// parcurge fisierul pana la linia 4
	while (rows < nrlinie) {
		char c = fgetc(file2);
		// fiind un sigur caracter il pot compara cu "=="
		if (c == '\n')
			// daca gasesc un caracter newline, trec la urmatoarea linie
			rows++;
	}
	// acum sunt la inceputul liniei 4

	// aloc memorie
	(**matrix)->photorgb = alloc_matrix_pixel((**matrix)->rows,
											  (**matrix)->columns);

	// citesc matricea
	for (int i = 0; i < (**matrix)->rows; i++) {
		for (int j = 0; j < (**matrix)->columns; j++) {
			unsigned char color;
			fread(&color, sizeof(unsigned char), 1, file2);
			((**matrix)->photorgb)[i][j].red = (int)(color);
			fread(&color, sizeof(unsigned char), 1, file2);
			((**matrix)->photorgb)[i][j].green = (int)(color);
			fread(&color, sizeof(unsigned char), 1, file2);
			((**matrix)->photorgb)[i][j].blue = (int)(color);
		}
	}

	// inchid fisierul
	fclose(file2);
}

void LOAD(const char *filename, image **matrix)
{
	// daca are o imagine incarcata o elibereaza
	if ((*matrix)->photo || (*matrix)->photorgb)
		free_photo(matrix);

	// deschid fisierul in format read
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to load %s\n", filename);
		if ((*matrix)->photo || (*matrix)->photorgb)
			free_photo(matrix);
		return;
	}

	// citesc tipul matricii
	fscanf(file, "%2s", (*matrix)->type);

	// type P1
	if (strcmp((*matrix)->type, "P1") == 0) {
		read_p1_ascii(&matrix, file);
		fclose(file);
	}

	// type P2
	if (strcmp((*matrix)->type, "P2") == 0) {
		read_p2_ascii(&matrix, file);
		fclose(file);
	}

	// type P3
	if (strcmp((*matrix)->type, "P3") == 0) {
		read_p3_ascii(&matrix, file);
		fclose(file);
	}

	// type P4 (citire din fisier binar)
	if (strcmp((*matrix)->type, "P4") == 0)
		read_p4_binary(&matrix, file, filename);

	// type P5
	if (strcmp((*matrix)->type, "P5") == 0)
		read_p5_binary(&matrix, file, filename);

	// type P6
	if (strcmp((*matrix)->type, "P6") == 0)
		read_p6_binary(&matrix, file, filename);

	// initializez coordonatele
	(*matrix)->x1 = 0;
	(*matrix)->x2 = (*matrix)->columns;
	(*matrix)->y1 = 0;
	(*matrix)->y2 = (*matrix)->rows;

	// afisez mesaj
	printf("Loaded %s\n", filename);
}
