#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include <QSet>
#include "selectiontool.h"
#include "tool.h"
#include <vector>

class PaintingArea;
class Shape;
class NavigationTool;
class QMdiSubWindow;
class LRectangle;
class QUndoStack;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    QMdiSubWindow* mActivePA;
    std::vector<Tool*> mActiveTools;
    QAction* mUndoAction;
    QAction* mRedoAction;
    QUndoStack* mUndoStack;
private:
    void activateTool(Tool* pTool);
    void deactivateTool(Tool::tool_type pTool);
    Tool* findActiveTool(Tool::tool_type pTool);
public:
    QUndoStack* getUndoStack(){return mUndoStack;};
    PaintingArea* createPaintingArea();
    bool openFile(const QString& pFileName);
    QMdiSubWindow* findMdiChild(const QString &fileName) const;
    bool loadFile(const QString& pFileName);
    std::vector<Tool*>& getActiveTools(){return mActiveTools;};
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
public slots:
    void newRectangleTool();
    void onRectangleToolComplete(LRectangle* pRect);
    void updateActivePA(QMdiSubWindow* pActivePA);
private slots:
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
};
#endif // MAINWINDOW_H
