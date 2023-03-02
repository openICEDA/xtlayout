#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include"commandcontrol.h"
#include<QSet>
#include"selectiontool.h"
class PaintingArea;
class Shape;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void newSelectionTool();
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
public slots:
    void newRectangleTool();
    void switchBackToSelectionTool();
private:
    enum ui_state{
        NO_ACTIVE_TOOL_STATE,
        INTERMEDIATE_STATE,
        TOOL_ACTIVE_STATE
    };
    ui_state mUiState;
    Ui::MainWindow* ui;
    PaintingArea* mPA;
    SelectionTool mSelectionTool;
    QMenu* file_menu;
};
#endif // MAINWINDOW_H
