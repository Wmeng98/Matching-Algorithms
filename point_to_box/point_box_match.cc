#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <exception>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

// Read in a text file detailing...
// *********************************
// - dimensions of a rectangular 2D bounding box, with any rotation and center point
// - A test point (inside or outside of the dimensions of the box)


struct point {
  float x;
  float y;
};

// dummy structure to represent basic box msg
struct box {
  // 32-bit float used for test
  // point center; // center of given box/rectangle
  // float width; // x-axis
  // float height; // y-axis

  vector<point> vertices; // sorted from NE [index 0], SE, SW, NW [index 3]
};

// Sorted from...
// Top Right, Bottom Right, Bottom Left, Top Left

// Assumption to simplify: input read is already sorted in this format
void getAndSortBoxVertices(string filename, vector<point> &vertices) {
  float x;
  float y;

  ifstream inFile;
  
  inFile.open(filename + ".txt");
  if (!inFile) {
      cout << "Unable to open file";
      exit(1); // terminate with error
  }
  int i = 0;
  while(i < 4) {
    inFile >> x;
    inFile >> y;

    // cout << "x: " << x;
    // cout << "y: " << y;

    point p;
    p.x = x;
    p.y = y;
    vertices.push_back(p);   
    
    i++; 
  }
  
  inFile.close();

}
void getTestPoint(point &testPoint) {
  float x, y;
  cin >> x;
  cin >> y;
  testPoint.x = x;
  testPoint.y = y;
}

// determine base vectors for dimensions of rectangle
void getVector(point &vertex1, point &vertex2, point &vector) {
  vector.x = vertex2.x - vertex1.x;
  vector.y = vertex2.y - vertex1.y;
}

float dotProduct(point &vector1, point &vector2) {
  return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

bool checkPointInDimensionD(point &vectorBaseD, point &vectorTest) {  // apply dot products
  cout << "dot Prod Base: " << dotProduct(vectorBaseD, vectorTest) << ", " << dotProduct(vectorBaseD, vectorBaseD) << endl;
  if (0 <= dotProduct(vectorBaseD, vectorTest) && dotProduct(vectorBaseD, vectorTest) <= dotProduct(vectorBaseD, vectorBaseD)) {
    return true; 
  } else {
    return false;
  }
}

bool checkPoint(point &vectorBaseX, point &vectorBaseY, point &vectorTestX, point &vectorTestY) {
  return checkPointInDimensionD(vectorBaseX, vectorTestX) && checkPointInDimensionD(vectorBaseY, vectorTestY);
}

int main(int argc, char const *argv[]) {
  box Rectangle;
  point testPoint;
  
  // vectors
  point AB;  
  point BC;
  point AM;
  point BM;
  // process inputs
  string filename = "box_input";
  if (argc > 1) { // first argument is name of executable
    cout << "filename given: " << argv[1] << endl;
    filename = argv[1];
  }
  getAndSortBoxVertices(filename, Rectangle.vertices);

  // process base vectors
  getVector(Rectangle.vertices[3], Rectangle.vertices[2], AB);
  getVector(Rectangle.vertices[2], Rectangle.vertices[1], BC);

  while(true) {
    cout << "Enter point to check: " << endl;
    getTestPoint(testPoint);

    // process input point "vectors"
    getVector(Rectangle.vertices[3], testPoint, AM);
    cout << "AM is: " << AM.x << ", " << AM.y << endl;;
    cout << "AB is: " << AB.x << ", " << AB.y << endl;;
    getVector(Rectangle.vertices[2], testPoint, BM);

    if (checkPoint(AB, BC, AM, BM)) {
      cout << "the point (" << testPoint.x << ", " << testPoint.y << ") is inside the rectangle" << endl;
    } else {
      cout << "the point (" << testPoint.x << ", " << testPoint.y << ") is NOT inside the rectangle" << endl;
    }
    cout << endl;
  }
  
}

