
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "save_exit.h"

void verify_word_is_int(int **x1, char *word, int *check)
{
	// convertesc after_select in int
	int x1_int = (int)atoi(word);
	char *back_to_string = (char *)malloc(10 * sizeof(char));

	// transform x1_int inapoi in char
	sprintf(back_to_string, "%d", x1_int);

	// compar cu cel citit initial (daca sunt la fel inseamna ca era numar)
	if (strcmp(back_to_string, word) == 0) {
		**x1 = x1_int;
	} else {
		printf("Invalid command\n");
		free(back_to_string);
		// daca afiseaza eroare, modific varibila de adevar
		*check = 0;
		return;
	}

	// eliberez memoria
	free(back_to_string);
}

void verify_coordinates_select(int *x1, int *y1, int *x2, int *y2,
							   char *after_select, image *photo,
							   char word_separator[])
{
	// presupun adevarat
	int check1 = 1;
	verify_word_is_int(&x1, after_select, &check1);
	// daca afiseaza eroare, ies din functie
	if (check1 == 0)
		return;

	// iau urmatorul cuvant
	char *y1_str = strtok(NULL, word_separator);
	if (y1_str) {
		int check2 = 1;
		verify_word_is_int(&y1, y1_str, &check2);
		// daca afiseaza eroare, ies din functie
		if (check2 == 0)
			return;
	} else {
		printf("Invalid command\n");
		return;
	}

	// iau urmatorul cuvant
	char *x2_str = strtok(NULL, word_separator);
	if (x2_str) {
		int check3 = 1;
		verify_word_is_int(&x2, x2_str, &check3);
		// daca afiseaza eroare, ies din functie
		if (check3 == 0)
			return;
	} else {
		printf("Invalid command\n");
		return;
	}

	// iau urmatorul cuvant
	char *y2_str = strtok(NULL, word_separator);
	if (y2_str) {
		int check4 = 1;
		verify_word_is_int(&y2, y2_str, &check4);
		// daca afiseaza eroare, ies din functie
		if (check4 == 0)
			return;
	} else {
		printf("Invalid command\n");
		return;
	}

	// daca am mai mult de 4 coordonate, afisez eroare
	char *excess = strtok(NULL, word_separator);
	if (excess) {
		printf("Invalid command\n");
		return;
	}

	// intru in functie daca toate cele de mai sus sunt in regula
	SELECT(&photo, *x1, *y1, *x2, *y2);
}

int main(void)
{
	image *photo = (image *)malloc(1 * sizeof(image));
	photo->photorgb = NULL;
	photo->photo = NULL;
	char *input = (char *)malloc(50 * sizeof(char));
	char word_separator[3] =  {' ', '\n', '\0'};

	// COMENZI
	while (fgets(input, 50, stdin)) {
		char *word = strtok(input, word_separator);

		// LOAD
		if (strcmp(word, "LOAD") == 0) {
			char *nume_fisier = strtok(NULL, word_separator);
			if (nume_fisier)
				LOAD(nume_fisier, &photo);
			else
				printf("Failed to load %s\n", nume_fisier);
		// SELECT
		} else if (strcmp(word, "SELECT") == 0) {
			char *after_select = strtok(NULL, word_separator);
			if (after_select) {
				// SELECT ALL
				if (strcmp(after_select, "ALL") == 0) {
					SELECT_ALL(&photo);
				// SELECT <x1> <x2> <y1> <y2>
				} else {
					int x1, y1, x2, y2;
					verify_coordinates_select(&x1, &y1, &x2, &y2,
											  after_select, photo,
											  word_separator);
				}
			} else {
				printf("Invalid command\n");
			}
		// HISTOGRAM
		} else if (strcmp(word, "HISTOGRAM") == 0) {
			HISTOGRAM(&photo, word_separator);
		// EQUALIZE
		} else if (strcmp(word, "EQUALIZE") == 0) {
			EQUALIZE(&photo);
		// ROTATE
		} else if (strcmp(word, "ROTATE") == 0) {
			int unghi;
			char *after_rotate = strtok(NULL, word_separator);
			if (after_rotate)
				unghi = (int)atoi(after_rotate);
			ROTATE(&photo, unghi);
		// CROP
		} else if (strcmp(word, "CROP") == 0) {
			CROP(&photo);
		// APPLY
		} else if (strcmp(word, "APPLY") == 0) {
			char *parametru = strtok(NULL, word_separator);
			if (parametru) {
				APPLY(&photo, parametru);
			} else {
				if (!photo->photo && !photo->photorgb)
					printf("No image loaded\n");
				else
					printf("Invalid command\n");
			}
		// SAVE
		} else if (strcmp(word, "SAVE") == 0) {
			char *nume_fisier = strtok(NULL, word_separator);
			char *ascii = strtok(NULL, word_separator);
			if (nume_fisier)
				SAVE(&photo, &nume_fisier, ascii);
		// EXIT
		} else if (strcmp(word, "EXIT") == 0) {
			EXIT(&photo, &input);
		// INVALID COMMAND
		} else {
			printf("Invalid command\n");
		}
	}
	return 0;
}
