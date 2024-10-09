// Farcasanu Bianca Ioana 313CAb 2023-2024

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "apply.h"

double sum(int a, int *frecv)
{
	double sum = 0;
	for (int i = 0; i <= a; i++)
		sum = sum + frecv[i];
	return sum;
}

double clamp_double(double f, int min, int max)
{
	if (f < min)
		return min;
	if (f > max)
		return max;
	return f;
}

void EQUALIZE(image **img)
{
	// verific daca am imagine incarcata in memorie
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

    // verific daca e de tipul P3 sau P6
	if (strcmp((*img)->type, "P3") == 0 || strcmp((*img)->type, "P6") == 0) {
		printf("Black and white image needed\n");
		return;
	}

    // verific daca e de tipul P2 sau P5
	if (strcmp((*img)->type, "P2") == 0 || strcmp((*img)->type, "P5") == 0) {
		// creez vectorul de frecventa
		int *frecv = (int *)calloc(256, sizeof(int));
		for (int i = 0; i < (*img)->rows; i++) {
			for (int j = 0; j < (*img)->columns; j++) {
				int aux = (*img)->photo[i][j];
				frecv[aux]++;
			}
		}

		double area = (*img)->rows * (*img)->columns;

		// inlocuiesc fiecare termen din matrice conform formulei
		for (int i = 0; i < (*img)->rows; i++) {
			for (int j = 0; j < (*img)->columns; j++) {
				int a = (*img)->photo[i][j];
				double f = (255 / area) * sum(a, frecv);
				f = clamp_double(f, 0, 255);
				int rez = round(f);
				(*img)->photo[i][j] = rez;
			}
		}

		// eliberez memoria pentru vector (nu mai am nevoie de el)
		free(frecv);

		// dupa ce fac toate operatiile afisez mesaj
		printf("Equalize done\n");
	}
}
