//
//  main.cpp
//  assignment3
//
//  Created by Marshal Foster on 1/15/19.
//  Copyright © 2019 Marshal Foster. All rights reserved.
//

#include <iostream>
#include <cmath>

struct cornerPoints {
  double x[4];
  double y[4];
  double length[4];
  double slope[4];
};

void getSideDistances(cornerPoints& shape){
  for (int i = 0; i < 3; ++i)
    shape.length[i] = sqrt(pow((shape.y[i+1] - shape.y[i]),2) + pow((shape.x[i+1] - shape.x[i]),2));
  shape.length[3] = sqrt(pow((shape.y[0] - shape.y[3]),2) + pow((shape.x[0] - shape.x[3]),2));
}

void getSideSlopes(cornerPoints& shape){
  for (int i = 0; i < 3; ++i)
    shape.slope[i] = (shape.y[i+1] - shape.y[i]) / (shape.x[i+1] - shape.x[i]);
  shape.slope[3] = (shape.y[0] - shape.y[3]) / (shape.x[0] - shape.x[3]);
}

bool isSquare(const cornerPoints& shape){
  return shape.y[1] == shape.x[3] && shape.x[1] == shape.x[2] && shape.x[1] == shape.y[2] && shape.x[1] == shape.y[3];
}

bool isRectangle(const cornerPoints& shape){
  return shape.x[1] == shape.x[2] && shape.y[1] == shape.x[3] && shape.y[2] == shape.y[3];
}

bool isParallelogram(cornerPoints& shape){
  getSideSlopes(shape);
  return shape.slope[0] == shape.slope[2] && shape.slope[1] == shape.slope[3];
}

bool isRhombus(cornerPoints& shape){
  getSideDistances(shape);
  return isParallelogram(shape) && shape.length[0] == shape.length[1] &&
    shape.length[0] == shape.length[2] && shape.length[0] == shape.length[3];
}

bool isTrapezoid(const cornerPoints& shape){
  return (shape.slope[0] == shape.slope[2]) != (shape.slope[1] == shape.slope[3]);
}

bool isKite(const cornerPoints& shape){
  return ((shape.length[0] == shape.length[3]) && (shape.length[1] == shape.length[2])) ||
    ((shape.length[0] == shape.length[1]) && (shape.length[2] == shape.length[3]));
}

void classifyQuadrilateral(cornerPoints& shape){
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
    std::cout << "quadrilateral" <<'\n';
}


int main(int argc, const char * argv[]) {
  while (!std::cin.eof()){
    cornerPoints shape;
    shape.x[0] = shape.y[0] = 0;
    std::cin >> shape.x[1] >> shape.y[1] >> shape.x[2] >> shape.y[2] >> shape.x[3] >> shape.y[3];
    classifyQuadrilateral(shape);
  }
  return 0;
}
