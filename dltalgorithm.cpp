#include "dltalgorithm.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <list>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <Eigen/Geometry>
#include <Eigen/Dense>

using namespace Eigen;
//using Eigen::MatrixXf;

DLTAlgorithm::DLTAlgorithm() {

}

QTransform* DLTAlgorithm::Execute(QVector<HomogeneousCoordinates*> nPoints, QVector<HomogeneousCoordinates*> nPrimPoints){
    QTransform* retMatrix;
    int nPointsSize = nPoints.size();
    int nPrimPointsSize = nPrimPoints.size();
    if ((nPointsSize < 4) || (nPrimPointsSize < 4)){
        // TODO: Obraditi gresku
    }

    if(nPointsSize != nPrimPointsSize){
        // TODO: Obraditi gresku
    }

    int rowCount = 2*nPointsSize;
    int colCount = 9;
    float** a = new float*[rowCount];
    for(int i = 0; i < rowCount; ++i)
        a[i] = new float[colCount];


    int entryIndex = 0;
    // Prolazimo kroz celu matricu A
    for(int i = 0; i < rowCount; i++){
        // Kada smo u parnoj vrsti, imamo jedan oblik
        // [0 0 0 -x3'x1 -x3'x2 -x3'x3 x2'x1 x2'x2 x2'x3]
        if (i % 2 ==0 ) {
            int columnIndex = 0;
            a[i][columnIndex] = 0;
            columnIndex++;
            a[i][columnIndex] = 0;
            columnIndex++;
            a[i][columnIndex] = 0;
            columnIndex++;
            a[i][columnIndex] = (-nPrimPoints[entryIndex]->x3) * nPoints[entryIndex]->x1;
            columnIndex++;
            a[i][columnIndex] = (-nPrimPoints[entryIndex]->x3) * nPoints[entryIndex]->x2;
            columnIndex++;
            a[i][columnIndex] = (-nPrimPoints[entryIndex]->x3) * nPoints[entryIndex]->x3;
            columnIndex++;
            a[i][columnIndex] = nPrimPoints[entryIndex]->x2 * nPoints[entryIndex]->x1;
            columnIndex++;
            a[i][columnIndex] = nPrimPoints[entryIndex]->x2 * nPoints[entryIndex]->x2;
            columnIndex++;
            a[i][columnIndex] = nPrimPoints[entryIndex]->x2 * nPoints[entryIndex]->x3;


        }
        // Kada smo u neparnoj vrsti imamo drugi oblik
        // [x3'x1 x3'x2 x3'x3 0 0 0 -x1'x1 -x1'x2 -x1'x3]
        else {
            int columnIndex = 0;
            a[i][columnIndex] = nPrimPoints[entryIndex]->x3 * nPoints[entryIndex]->x1;
            columnIndex++;
            a[i][columnIndex] = nPrimPoints[entryIndex]->x3 * nPoints[entryIndex]->x2;
            columnIndex++;
            a[i][columnIndex] = nPrimPoints[entryIndex]->x3 * nPoints[entryIndex]->x3;
            columnIndex++;
            a[i][columnIndex] = 0;
            columnIndex++;
            a[i][columnIndex] = 0;
            columnIndex++;
            a[i][columnIndex] = 0;
            columnIndex++;
            a[i][columnIndex] = (-nPrimPoints[entryIndex]->x1) * nPoints[entryIndex]->x1;
            columnIndex++;
            a[i][columnIndex] = (-nPrimPoints[entryIndex]->x1) * nPoints[entryIndex]->x2;
            columnIndex++;
            a[i][columnIndex] = (-nPrimPoints[entryIndex]->x1) * nPoints[entryIndex]->x3;


        }


        if(i % 2 == 1){
            entryIndex++;
        }
    }

    /*for (int i = 0; i < 8; i++)
        for (int j = 0; j < 9; j++)
            std::cout << "[" << i <<"][" << j << "]" << a[i][j] << std::endl;*/

   MatrixXf m(rowCount, colCount);
   for(int i=0; i<rowCount; ++i)
   {
       for(int j=0; j<colCount; ++j)
       {
            m(i,j) = a[i][j];
       }
   }



   JacobiSVD<MatrixXf> svd(m, ComputeFullU | ComputeFullV);
   MatrixXf v = svd.matrixV();

    //dsvd(a, rowCount, colCount, w, v);



    retMatrix = new QTransform(v.coeff(0,8), v.coeff(1,8), v.coeff(2,8),
                               v.coeff(3,8), v.coeff(4,8), v.coeff(5,8),
                               v.coeff(6,8), v.coeff(7,8), v.coeff(8,8));



    return retMatrix;
}
