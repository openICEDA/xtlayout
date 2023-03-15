#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include "commandcontrol.h"
#include <QSet>
#include "selectiontool.h"
#include "tool.h"
#include <vector>

class PaintingArea;
class Shape;
class NavigationTool;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
public slots:
    void newRectangleTool();
    void switchBackToSelectionTool();
private:
    NavigationTool* mNavTool; //TODO: consider unique_ptr
    Ui::MainWindow* ui;
    PaintingArea* mPA;
    QMenu* file_menu;
};
#endif // MAINWINDOW_H
