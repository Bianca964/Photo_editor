
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "image_struct.h"

void free_matrix_int(int **matrix, int rows)
{
	for (int i = 0; i < rows; i++)
		free(matrix[i]);
	free(matrix);
}

void free_matrix_pixel(pixel **matrix, int rows)
{
	for (int i = 0; i < rows; i++)
		free(matrix[i]);
	free(matrix);
}

int **alloc_matrix_int(int rows, int columns)
{
	// aloc memorie
	int **matrix = (int **)malloc(rows * sizeof(int *));
	if (!matrix) {
		printf("Matrix allocation failed\n");
		return NULL;
	}
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int *)malloc(columns * sizeof(int));
		if (!matrix[i]) {
			printf("Matrix allocation failed\n");
			free_matrix_int(matrix, i);
			return NULL;
		}
	}
	return matrix;
}

void read_matrix_int(int ***matrix, int rows, int columns, FILE *file)
{
	for (int i = 0; i < rows; i++) {
		for (int j =  0; j < columns; j++)
			fscanf(file, "%d", &(*matrix)[i][j]);
	}
}

pixel **alloc_matrix_pixel(int rows, int columns)
{
	pixel **matrix = (pixel **)malloc(rows * sizeof(pixel *));
	if (!matrix) {
		printf("Matrix allocation failed\n");
		return NULL;
	}
	for (int i = 0; i < rows; i++) {
		matrix[i] = (pixel *)malloc(columns * sizeof(pixel));
		if (!matrix[i]) {
			printf("Matrix allocation failed\n");
			free_matrix_pixel(matrix, i);
			return NULL;
		}
	}
	return matrix;
}

void read_matrix_pixel(pixel **matrix, int rows, int columns, FILE *file)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int r, g, b;
			fscanf(file, "%d %d %d", &r, &g, &b);
			matrix[i][j].red = r;
			matrix[i][j].green = g;
			matrix[i][j].blue = b;
		}
	}
}

void free_photo(image **matrix)
{
    // daca exista imagine grayscale sau alb-negru o elibereaza
	if ((*matrix)->photo) {
		free_matrix_int((*matrix)->photo, (*matrix)->rows);
		(*matrix)->photo = NULL;
	}

    // daca exista imagine color incarcata o elibereaza
	if ((*matrix)->photorgb) {
		free_matrix_pixel((*matrix)->photorgb, (*matrix)->rows);
		(*matrix)->photorgb = NULL;
	}
}
