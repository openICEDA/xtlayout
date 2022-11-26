#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include"commandcontrol.h"
#include<QSet>
class PaintingArea;
class Shape;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void newRectangleTool();
private:
    enum ui_state{
        NO_ACTIVE_TOOL_STATE,
        INTERMEDIATE_STATE,
        TOOL_ACTIVE_STATE
    };
    ui_state mUiState;
    PaintingArea *mPA;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
