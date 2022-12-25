#include <stdio.h>

// Struct for representing a point in 2D space
typedef struct {
  double x;
  double y;
} Point;

// Function for generating a Sierpinski carpet from a point, a size, and an iteration number
void sierpinski(Point p, double size, int iteration, FILE* fp) {
  if (iteration == 0) {
    // Base case: draw a filled rectangle
    fprintf(fp, "  <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"black\" />\n", p.x, p.y, size, size);
  } else {
    // Recursive case: divide the area into nine smaller rectangles and generate a Sierpinski carpet for each
    double newSize = size / 3.0;
    int i, j;

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        // Skip the center rectangle
        if (i == 1 && j == 1) continue;

        Point newPoint;
        newPoint.x = p.x + j * newSize;
        newPoint.y = p.y + i * newSize;
        sierpinski(newPoint, newSize, iteration - 1, fp);
      }
    }
  }
}

int main() {
  // Open an SVG file for writing
  FILE* fp = fopen("sierpinski.svg", "w");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // Set the width and height of the SVG image
  int width = 600;
  int height = 600;

  // Write the SVG header
  fprintf(fp, "<svg width=\"%d\" height=\"%d\">\n", width, height);

  // Define the starting point and size of the Sierpinski carpet
  Point p;
  p.x = 0;
  p.y = 0;
  double size = 600;

  // Generate the Sierpinski carpet
  sierpinski(p, size, 4, fp);

  // Close the SVG element
  fprintf(fp, "</svg>\n");

  // Close the file
  fclose(fp);

  return 0;
}
