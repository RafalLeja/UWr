#include <stdio.h>
#include <math.h>

#define M_PI 3.1415
// Struct for representing a point in 2D space
typedef struct {
  double x;
  double y;
} Point;

// Function for generating a Pythagoras tree from a point, a size, an angle, and an iteration number
void pythagoras(Point p, double size, double angle, int iteration, FILE* fp) {
  if (iteration == 0) {
    // Base case: draw a line
    Point p2, p3;
    p2.x = p.x + size * cos(angle);
    p2.y = p.y + size * sin(angle);

    p3.x = p2.x + size * cos(angle);
    p3.y = p2.y + size * sin(angle);

    fprintf(fp, "  <path d=\"M %f %f L %f %f L %f %f\" stroke=\"black\" stroke-width=\"1\" fill=\"none\" />\n", p.x, p.y, p2.x, p2.y, p3.x, p3.y);
  } else {
    // Recursive case: draw two lines and generate two Pythagoras trees
    Point p2, p3;
    double angle1, angle2;

    // Calculate the angle of the left branch
    angle1 = angle + M_PI / 4.0;

    // Calculate the end point of the left branch
    p2.x = p.x + size * cos(angle1);
    p2.y = p.y + size * sin(angle1);

    // Generate the left branch
    pythagoras(p2, size / sqrt(2.0), angle1, iteration - 1, fp);

    // Calculate the angle of the right branch
    angle2 = angle - M_PI / 4.0;

    // Calculate the end point of the right branch
    p3.x = p2.x + size * cos(angle2);
    p3.y = p2.y + size * sin(angle2);

    // Generate the right branch
    pythagoras(p3, size / sqrt(2.0), angle2, iteration - 1, fp);
  }
}

int main() {
  // Open an SVG file for writing
  FILE* fp = fopen("pythagoras.svg", "w");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // Set the width and height of the SVG image
  int width = 600;
  int height = 600;

  // Write the SVG header
  fprintf(fp, "<svg width=\"%d\" height=\"%d\">\n", width, height);
  // Generate the Pythagoras tree
  Point p;
  p.x = 300;
  p.y = 500;
  double size = 200;


  pythagoras(p, size, M_PI / 2.0, 1, fp);

  // Close the SVG element
  fprintf(fp, "</svg>\n");

  // Close the file
  fclose(fp);

  return 0;
}
