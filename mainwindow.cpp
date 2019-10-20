#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QStringList>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    naiveAlgorithm(new NaiveAlgorithm()),
    dltAlgorithm(new DLTAlgorithm())
{
    ui->setupUi(this);

    scene = new ImageScene(this);

    QHBoxLayout *layout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    ui->labelImage->setLayout(layout);

    //connect(ui->browseImage, SIGNAL(clicked()), this, SLOT(on_browseImage_clicked()));
    connect(ui->selectCoordinates, SIGNAL(clicked(bool)), this, SLOT(on_selectCoordinates_clicked()));
    connect(ui->pbExecuteAlgorithm, SIGNAL(clicked(bool)), this, SLOT(on_pbExecuteAlgorithm_clicked()));

    connect(scene, SIGNAL(addNewPoint(QGraphicsSceneMouseEvent*)),
            this, SLOT(addNewPoint(QGraphicsSceneMouseEvent*)));

    ui->cbAlgorithmType->addItem("Naive algorithm");
    ui->cbAlgorithmType->addItem("DLT algorithm");
    ui->cbAlgorithmType->addItem("Modified DLT algorithm");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewPoint(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (points.size() >= POINTS_SIZE)
    {
        QMessageBox Msgbox;
        Msgbox.setText("You have already selected 4 points. Please, execute the algorith.");
        Msgbox.exec();
        return;
    }

    double rad = 1;
    QPointF pt = mouseEvent->scenePos();
    QColor red(Qt::red);
    scene->addEllipse(pt.x()-rad, pt.y()-rad, 10, 10, QPen(), QBrush(red, Qt::SolidPattern));

    points.append(pt);

    if (points.size() == POINTS_SIZE)
    {
        ui->labelAvalue->setText("(" + QString::number(points.at(0).x()) + ", " + QString::number(points.at(0).y()) + ")");
        ui->labelBvalue->setText("(" + QString::number(points.at(1).x()) + ", " + QString::number(points.at(1).y()) + ")");
        ui->labelCvalue->setText("(" + QString::number(points.at(2).x()) + ", " + QString::number(points.at(2).y()) + ")");
        ui->labelDvalue->setText("(" + QString::number(points.at(3).x()) + ", " + QString::number(points.at(3).y()) + ")");
    }
}

void MainWindow::on_browseImage_clicked()
{
    // Do nothing, temporarly

    /*QString lastLoadedImagePath;
    QString filter;
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Add Image File", lastLoadedImagePath, filter);

    QUrl imagePath = fileNames.front();
    QPixmap imagePixmap = imagePath.path();

    ui->labelImage->setPixmap(imagePixmap);
    ui->labelImage->setScaledContents(true);
    ui->labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);*/
}

void MainWindow::on_selectCoordinates_clicked()
{

}

void MainWindow::on_pbExecuteAlgorithm_clicked()
{
    if (points.size() < POINTS_SIZE)
    {
        QMessageBox Msgbox;
        Msgbox.setText(" Please, select 4 points on the white screen.");
        Msgbox.exec();
    }

    QVector<HomogeneousCoordinates*> homogeneousCoordinates
    {
        new HomogeneousCoordinates(points.at(0).x(), points.at(0).y(), 1),
        new HomogeneousCoordinates(points.at(1).x(), points.at(1).y(), 1),
        new HomogeneousCoordinates(points.at(2).x(), points.at(2).y(), 1),
        new HomogeneousCoordinates(points.at(3).x(), points.at(3).y(), 1),
    };

    QTransform* matrix;
    switch (ui->cbAlgorithmType->currentIndex()) {
    case 0:
        matrix = naiveAlgorithm->Execute(homogeneousCoordinates, homogeneousCoordinates);
        break;
    case 1:
        matrix = dltAlgorithm->Execute(homogeneousCoordinates, homogeneousCoordinates);
        break;
    default:
        break;
    }

    ui->matrixRow1->setText("[" + QString::number(matrix->m11()) + ", " + QString::number(matrix->m12())+ ", " + QString::number(matrix->m13()));
    ui->matrixRow2->setText(QString::number(matrix->m21()) + ", " + QString::number(matrix->m22())+ ", " + QString::number(matrix->m23()));
    ui->matrixRow3->setText(QString::number(matrix->m31()) + ", " + QString::number(matrix->m32())+ ", " + QString::number(matrix->m33()) + "]");
}
