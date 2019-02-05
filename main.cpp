//
//  main.cpp
//  assignment3
//
//  Created by Marshal Foster on 1/15/19.
//  Copyright © 2019 Marshal Foster. All rights reserved.
//

#include <cmath>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Used to represent a quadrilateral.
struct cornerPoints {
  // The four X coordinates. x[0] is always equal to 0.
  double x[4];
  // The four Y coordinates. y[0] is always equal to 0.
  double y[4];
  // length 0 starts at point 0 and ends at point 1.
  // length 3 starts at point 3 and ends at point 0;
  double length[4];
  // slope 0 starts at point 0 and ends at point 1.
  // slope3 starts at point 3 and ends at point 0;
  double slope[4];
};

/* Used to test the error 1 condition that the string input must only
 * contain the digits 0-9 and spaces used to speperate each of the six
 * input numbers.
 */
bool containsIllegalChars(const std::string &line) {
  for (char c : line) {
    if (!isdigit(c) && c != ' ')
      return true;
  }
  return false;
}

// Determines if three points are collinear in order to test condition four.
// Returns 1 if the points are collinear, else false.
bool isCollinear(const int &x1, const int &y1, const int &x2, const int &y2,
                 const int &x3, const int &y3) {
  return ((y3 - y2) * (x2 - x1) == (y2 - y1) * (x3 - x2));
}

// Determins the orentation, clockwise or counterclockwise, of three points.
// Returns 1 of clockwise and 2 for counterclockwise.
int orientation(const int &x1, const int &y1, const int &x2, const int &y2,
                const int &x3, const int &y3) {
  int val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
  return (val > 0) ? 1 : 2;
}

// Returns true if any points are less than 0 or greater than 100.
bool isError1(const std::vector<int> &numbers) {
  if (numbers.size() != 6)
    return true;
  for (int i : numbers) {
    if (i < 0 || i > 100)
      return true;
  }
  return false;
}

// Returns true if any two points coincide.
bool isError2(cornerPoints &shape) {
  for (int i = 0; i < 4; i++)
    assert((shape.x[i] > -1 && shape.x[i] < 101) &&
           (shape.y[i] > -1 && shape.y[i] < 101));
  for (int i = 0, j = 1; i < 4; i++, j++) {
    for (int k = j; k < 4; k++) {
      if (shape.x[i] == shape.x[k] && shape.y[i] == shape.y[k])
        return true;
    }
  }
  return false;
}

// Returns true if any two line segments representing sides cross each other.
bool isError3(cornerPoints &shape) {
  for (int i = 0; i < 4; i++)
    assert((shape.x[i] > -1 && shape.x[i] < 101) &&
           (shape.y[i] > -1 && shape.y[i] < 101));
  if ((orientation(shape.x[0], shape.y[0], shape.x[1], shape.y[1], shape.x[3],
                   shape.y[3])) !=
          (orientation(shape.x[0], shape.y[0], shape.x[1], shape.y[1],
                       shape.x[2], shape.y[2])) &&
      (orientation(shape.x[3], shape.y[3], shape.x[2], shape.y[2], shape.x[0],
                   shape.y[0])) !=
          (orientation(shape.x[3], shape.y[3], shape.x[2], shape.y[2],
                       shape.x[1], shape.y[1])))
    return true;
  else if ((orientation(shape.x[0], shape.y[0], shape.x[3], shape.y[3],
                        shape.x[1], shape.y[1])) !=
               (orientation(shape.x[0], shape.y[0], shape.x[3], shape.y[3],
                            shape.x[2], shape.y[2])) &&
           (orientation(shape.x[1], shape.y[1], shape.x[2], shape.y[2],
                        shape.x[0], shape.y[0])) !=
               (orientation(shape.x[1], shape.y[1], shape.x[2], shape.y[2],
                            shape.x[3], shape.y[3])))
    return true;
  else
    return false;
}

// Returns true if any three points are colinear
bool isError4(cornerPoints &shape) {
  for (int i = 0; i < 4; i++)
    assert((shape.x[i] > -1 && shape.x[i] < 101) &&
           (shape.y[i] > -1 && shape.y[i] < 101));
  int points[4][3];
  points[0][0] = points[2][2] = points[3][1] = 0;
  points[0][1] = points[1][0] = points[3][2] = 1;
  points[0][2] = points[1][1] = points[2][0] = 2;
  points[1][2] = points[2][1] = points[3][0] = 3;
  for (int i = 0; i < 4; i++) {
    if (isCollinear(shape.x[points[i][0]], shape.y[points[i][0]],
                    shape.x[points[i][1]], shape.y[points[i][1]],
                    shape.x[points[i][2]], shape.y[points[i][2]]))
      return true;
  }
  return false;
}

// Parses an input string into ints seperated by spaces.
std::vector<int> parseLinetoInts(const std::string &str) {
  std::vector<std::string> temp;
  std::vector<int> ret;
  std::stringstream ss(str);
  std::string digit;
  while (getline(ss, digit, ' '))
    temp.push_back(digit);
  for (std::string s : temp) {
    ret.push_back(std::stoi(s));
  }
  return ret;
}

void getSideDistances(cornerPoints &shape) {
  for (int i = 0; i < 3; ++i)
    shape.length[i] = sqrt(pow((shape.y[i + 1] - shape.y[i]), 2) +
                           pow((shape.x[i + 1] - shape.x[i]), 2));
  shape.length[3] = sqrt(pow((shape.y[0] - shape.y[3]), 2) +
                         pow((shape.x[0] - shape.x[3]), 2));
}

void getSideSlopes(cornerPoints &shape) {
  for (int i = 0; i < 3; ++i)
    shape.slope[i] =
        (shape.y[i + 1] - shape.y[i]) / (shape.x[i + 1] - shape.x[i]);
  shape.slope[3] = (shape.y[0] - shape.y[3]) / (shape.x[0] - shape.x[3]);
}

bool isSquare(const cornerPoints &shape) {
  return shape.y[1] == shape.x[3] && shape.x[1] == shape.x[2] &&
         shape.x[1] == shape.y[2] && shape.x[1] == shape.y[3];
}

bool isRectangle(const cornerPoints &shape) {
  return shape.x[1] == shape.x[2] && shape.y[1] == shape.x[3] &&
         shape.y[2] == shape.y[3];
}

bool isParallelogram(cornerPoints &shape) {
  getSideSlopes(shape);
  return shape.slope[0] == shape.slope[2] && shape.slope[1] == shape.slope[3];
}

bool isRhombus(cornerPoints &shape) {
  getSideDistances(shape);
  return isParallelogram(shape) && shape.length[0] == shape.length[1] &&
         shape.length[0] == shape.length[2] &&
         shape.length[0] == shape.length[3];
}

bool isTrapezoid(const cornerPoints &shape) {
  return (shape.slope[0] == shape.slope[2]) !=
         (shape.slope[1] == shape.slope[3]);
}

bool isKite(const cornerPoints &shape) {
  return ((shape.length[0] == shape.length[3]) &&
          (shape.length[1] == shape.length[2])) ||
         ((shape.length[0] == shape.length[1]) &&
          (shape.length[2] == shape.length[3]));
}

void classifyQuadrilateral(cornerPoints &shape) {
  if (isSquare(shape))
    std::cout << "square" << '\n';
  else if (isRectangle(shape))
    std::cout << "rectangle" << '\n';
  else if (isRhombus(shape))
    std::cout << "rhombus" << '\n';
  else if (isParallelogram(shape))
    std::cout << "parallelogram" << '\n';
  else if (isTrapezoid(shape))
    std::cout << "trapezoid" << '\n';
  else if (isKite(shape))
    std::cout << "kite" << '\n';
  else
    std::cout << "quadrilateral" << '\n';
}

int main(int argc, const char *argv[]) {
  while (!std::cin.eof()) {
    cornerPoints shape;
    std::string line;
    getline(std::cin, line);
    if (containsIllegalChars(line)) {
      std::cout << "error 1";
      exit(11);
    }
    std::vector<int> numbers = parseLinetoInts(line);
    if (isError1(numbers)) {
      std::cout << "error 1";
      exit(11);
    }
    shape.x[0] = shape.y[0] = 0;
    for (int i = 0, j = 1; j < 4; i += 2, j++) {
      assert(numbers[i] > -1);
      shape.x[j] = numbers[i];
      shape.y[j] = numbers[i + 1];
    }
    if (isError2(shape)) {
      std::cout << "error 2";
      exit(12);
    }
    if (isError4(shape)) {
      std::cout << "error 4";
      exit(14);
    }
    if (isError3(shape)) {
      std::cout << "error 3";
      exit(13);
    }
    classifyQuadrilateral(shape);
  }
  return 0;
}

/*
 // Used for developer testing within Xcode.
 std::ifstream myfile;
 myfile.open ("input.txt");
 std::string line;
 while (std::getline(myfile, line)){
 cornerPoints shape;
 std::cout << line << '\n';
 if (containsIllegalChars(line)){
 std::cout << "error 1";
 return 1;
 }
 std::vector<int> numbers = parseLinetoInts(line);
 if (isError1(numbers)){
 std::cout << "error 1";
 return 1;
 }
 shape.x[0] = shape.y[0] = 0;
 for ( int i = 0, j = 1; j < 4; i+=2, j++){
 shape.x[j] = numbers[i];
 shape.y[j] = numbers[i+1];
 }
 if (isError2(shape)){
 std::cout << "error 2";
 return 1;
 }
 if (isError4(shape)){
 std::cout << "error 4";
 return 1;
 }
 if (isError3(shape)){
 std::cout << "error 3";
 return 1;
 }
 classifyQuadrilateral(shape);
 }
 */
