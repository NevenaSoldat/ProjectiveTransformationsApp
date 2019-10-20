#ifndef HOMOGENEOUSCOORDINATES_H
#define HOMOGENEOUSCOORDINATES_H

struct HomogeneousCoordinates{

  HomogeneousCoordinates(float x, float y, float z) {
        x1 = x;
        x2 = y;
        x3 = z;
  }

  float x1;
  float x2;
  float x3;
};

#endif // HOMOGENEOUSCOORDINATES_H
