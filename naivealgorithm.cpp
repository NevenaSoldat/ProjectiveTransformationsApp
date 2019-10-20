#include "naivealgorithm.h"
#include "homogeneouscoordinates.h"
#include <QGenericMatrix>
#include <QTransform>
#include <iostream>

NaiveAlgorithm::NaiveAlgorithm() {

}

QTransform* NaiveAlgorithm::Execute(QVector<HomogeneousCoordinates*> entryPoints,
                                    QVector<HomogeneousCoordinates*> entryPrimPoints) {
    QTransform* retMatrix;

    // Matrica preslikavanja P1 (preslikavanje f)
    QTransform* matrixP1 = CalculateMatrix(entryPoints);

    // Ispis matrice P1
    std::cout << "MATRICA P1: " << std::endl;
    std::cout << matrixP1->m11() << " " << matrixP1->m12() << " " << matrixP1->m13() << std::endl;
    std::cout << matrixP1->m21() << " " << matrixP1->m22() << " " << matrixP1->m23() << std::endl;
    std::cout << matrixP1->m31() << " " << matrixP1->m32() << " " << matrixP1->m33() << std::endl;

    // Matrica preslikavanja P2 (preslikavanje g)
    QTransform* matrixP2 = CalculateMatrix(entryPrimPoints);

    // Ispis matrice P2
    std::cout << "MATRICA P2: " << std::endl;
    std::cout << matrixP2->m11() << " " << matrixP2->m12() << " " << matrixP2->m13() << std::endl;
    std::cout << matrixP2->m21() << " " << matrixP2->m22() << " " << matrixP2->m23() << std::endl;
    std::cout << matrixP2->m31() << " " << matrixP2->m32() << " " << matrixP2->m33() << std::endl;

    // Matrica projektivnog preslikavanja P2*P1^-1 (fog^-1)
    retMatrix = new QTransform(matrixP2->operator *(matrixP1->inverted()));

    return retMatrix;
}

// Funkcija racuna matrice P1 i P2
QTransform* NaiveAlgorithm::CalculateMatrix(QVector<HomogeneousCoordinates*> coordinates){
    QTransform* retMatrix;
    HomogeneousCoordinates* A = coordinates[0];
    HomogeneousCoordinates* B = coordinates[1];
    HomogeneousCoordinates* C = coordinates[2];
    HomogeneousCoordinates* D = coordinates[3];

    QTransform* systemMatrix = new QTransform(A->x1, B->x1, C->x1,
                                              A->x2, B->x2, C->x2,
                                              A->x3, B->x3, C->x3);

    float systemDeterminant = systemMatrix->determinant();

    QTransform* det1 = new QTransform(D->x1, B->x1, C->x1,
                                      D->x2, B->x2, C->x2,
                                      D->x3, B->x3, C->x3);

    float firstDeterminant = det1->determinant();
    float lambda1 = firstDeterminant/systemDeterminant;

    QTransform* det2 = new QTransform(A->x1, D->x1, C->x1,
                                      A->x2, D->x2, C->x2,
                                      A->x3, D->x3, C->x3);
    float secondDeterminant = det2->determinant();
    float lambda2 = secondDeterminant/systemDeterminant;

    QTransform* det3 = new QTransform(A->x1, B->x1, D->x1,
                                      A->x2, B->x2, D->x2,
                                      A->x3, B->x3, D->x3);
    float thirdDeterminant = det3->determinant();
    float lambda3 = thirdDeterminant/systemDeterminant;

    retMatrix = new QTransform(lambda1*systemMatrix->m11(), lambda2*systemMatrix->m12(), lambda3*systemMatrix->m13(),
                               lambda1*systemMatrix->m21(), lambda2*systemMatrix->m22(), lambda3*systemMatrix->m23(),
                               lambda1*systemMatrix->m31(), lambda2*systemMatrix->m32(), lambda3*systemMatrix->m33());


    QTransform* projectiveMatrix = retMatrix;

    return projectiveMatrix;
}
