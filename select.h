
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "load.h"

void interchange(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void SELECT(image **img, int x1, int y1, int x2, int y2)
{
	// verific daca nu exista niciun fisier incarcat
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	// verific daca coordonatele sunt valide
	if (x1 > (*img)->columns || x2 > (*img)->columns || y1 > (*img)->rows ||
		y2 > (*img)->rows || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 ||
		x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return;
	}

	// le ordonez crescator
	if (x2 < x1)
		interchange(&x1, &x2);
	if (y2 < y1)
		interchange(&y1, &y2);

	// le retin in structura
	(*img)->x1 = x1;
	(*img)->y1 = y1;
	(*img)->x2 = x2;
	(*img)->y2 = y2;

	// afisez mesaj
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

void SELECT_ALL(image **img)
{
	// daca imaginea nu exista
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	// modific coordonatele
	(*img)->x1 = 0;
	(*img)->x2 = (*img)->columns;
	(*img)->y1 = 0;
	(*img)->y2 = (*img)->rows;

	// afisez mesaj
	printf("Selected ALL\n");
}
