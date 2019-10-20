#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagescene.h"
#include "naivealgorithm.h"
#include "dltalgorithm.h"
#include <QObject>
#include <QMainWindow>
#include <QVector>

#define POINTS_SIZE 4

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void addNewPoint(QGraphicsSceneMouseEvent* mouseEvent);

    void on_browseImage_clicked();
    void on_selectCoordinates_clicked();
    void on_pbExecuteAlgorithm_clicked();

private:
    Ui::MainWindow* ui;

    ImageScene *scene;
    QGraphicsView *view;

    NaiveAlgorithm* naiveAlgorithm;
    DLTAlgorithm* dltAlgorithm;

    QVector<QPointF> points;
};

#endif // MAINWINDOW_H
