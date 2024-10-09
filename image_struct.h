
typedef struct {
	int red;
	int green;
	int blue;
} pixel;

typedef struct {
	int rows;
	int columns;
	int **photo;
	pixel **photorgb;
	int x1, x2, y1, y2;
	char type[3];
} image;
