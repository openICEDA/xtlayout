#include "mainwindow.h"

#include <QApplication>
#include "matrix.h"
#include <vector>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Matrix m1 = Matrix::mat3(1,1,1,0,1,0,0,0,1);
    Matrix m2 = Matrix::mat3(1,1,1,0,1,0,0,0,1);
    return a.exec();
}
