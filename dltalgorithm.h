#ifndef DLTALGORITHM_H
#define DLTALGORITHM_H

#include "homogeneouscoordinates.h"
#include <QTransform>

class DLTAlgorithm {
public:
    DLTAlgorithm();
    QTransform* Execute(QVector<HomogeneousCoordinates*> nPoints, QVector<HomogeneousCoordinates*> nPrimPoints);

private:

};

#endif // DLTALGORITHM_H
