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
class QMdiSubWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    NavigationTool* mNavTool; //TODO: consider unique_ptr
    Ui::MainWindow* ui;
    QMdiSubWindow* mActivePA;
    QMenu* file_menu;
    std::vector<Tool*> mActiveTools;
private:
    void activateTool(Tool* pTool);
    void deactivateTool(Tool::tool_type pTool);
    Tool* findActiveTool(Tool::tool_type pTool);
public:
    std::vector<Tool*>& getActiveTools(){return mActiveTools;};
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
public slots:
    void newRectangleTool();
    void switchBackToSelectionTool();
    void updateActivePA(QMdiSubWindow* pActivePA);
private slots:
    void on_actionNew_triggered();
};
#endif // MAINWINDOW_H
