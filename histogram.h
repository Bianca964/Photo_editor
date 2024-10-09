// Farcasanu Bianca Ioana 313CAb 2023-2024

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "select.h"

void HISTOGRAM(image **img, char word_separator[])
{
	// daca nu exista fisier incarcat
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	// citesc numerele de la tastatura sa verific daca e invalid command
	char *after_histogram1 = strtok(NULL, word_separator);
	if (!after_histogram1) {
		printf("Invalid command\n");
		return;
	}

	// citesc numerele de dupa si verific daca sunt 2 si daca sunt numere
	int nr1 = (int)atoi(after_histogram1);
	char *aux1 = (char *)malloc(7 * sizeof(char));
	sprintf(aux1, "%d", nr1);
	if (strcmp(aux1, after_histogram1) != 0) {
		printf("Invalid command\n");
		return;
	}
	free(aux1);

	char *after_histogram2 = strtok(NULL, word_separator);
	if (after_histogram2) {
		int nr2 = (int)atoi(after_histogram2);
		char *aux2 = (char *)malloc(7 * sizeof(char));
		sprintf(aux2, "%d", nr2);
		if (strcmp(aux2, after_histogram2) != 0) {
			printf("Invalid command\n");
			return;
		}
		free(aux2);
	} else {
		printf("Invalid command\n");
		return;
	}

	// verific daca are mai multe cuvinte decat trebuie
	char *excess = strtok(NULL, word_separator);
	if (excess) {
		printf("Invalid command\n");
		return;
	}

	// daca imaginea este color afiseaza mesaj
	if (strcmp((*img)->type, "P3") == 0 || strcmp((*img)->type, "P6") == 0) {
		printf("Black and white image needed\n");
		return;
	}
}

void ROTATE(image **img, int unghi)
{
	// verific daca am imagine incarcata in memorie
	if (!(*img)->photo && !(*img)->photorgb) {
		printf("No image loaded\n");
		return;
	}

	// daca nu e un unghi acceptat afisez eroare
	if (abs(unghi) != 90 && abs(unghi) != 180 && abs(unghi) != 270 &&
		abs(unghi) != 360 && abs(unghi) != 0) {
		printf("Unsupported rotation angle\n");
		return;
	}

	// usurez notatiile
	int x1 = (*img)->x1;
	int y1 = (*img)->y1;
	int x2 = (*img)->x2;
	int y2 = (*img)->y2;
	int rows = (*img)->rows;
	int columns = (*img)->columns;

	// verific inainte daca e selectata toata imaginea
	if (x1 == 0 && x2 == columns && y1 == 0 && y2 == rows) {
		if (abs(unghi) == 360 || abs(unghi) == 0) {
			printf("Rotated %d\n", unghi);
			return;
		}
		// aici ar trebui sa rotesc cu 90, 180, 270 toata imaginea
		printf("Rotated %d\n", unghi);
		return;
	}

	// daca nu e selectata toata imaginea, tb facut separat pentru nxn selectat
	if ((x2 - x1) != (y2 - y1)) {
		printf("The selection must be square\n");
		return;
	}

	if (abs(unghi) == 360 || abs(unghi) == 0) {
		printf("Rotated %d\n", unghi);
		return;
	}
}
