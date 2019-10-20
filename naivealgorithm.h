#ifndef NAIVEALGORITHM_H
#define NAIVEALGORITHM_H

#include "homogeneouscoordinates.h"
#include <QVector>
#include <QGenericMatrix>

class NaiveAlgorithm
{
public:
    NaiveAlgorithm();
    QTransform* Execute(QVector<HomogeneousCoordinates*> entryPoints,
                        QVector<HomogeneousCoordinates*> entryPrimPoints);

private:
    QTransform* CalculateMatrix(QVector<HomogeneousCoordinates*> primCoordinates);

};

#endif // NAIVEALGORITHM_H
