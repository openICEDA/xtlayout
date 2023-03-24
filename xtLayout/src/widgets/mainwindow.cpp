#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QToolButton>
#include <QMdiSubWindow>
#include "drawcommand.h"
#include "rectangletool.h"
#include "selectiontool.h"
#include "navigationtool.h"
#include "xtdb.h"
using namespace xtdb;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setVisible(true);
    setCentralWidget(ui->mdiArea);
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::updateActivePA);

    QToolButton *rectToolButton = new QToolButton(this);
    QToolButton *selectToolButton = new QToolButton(this);
    ui->toolBar->addWidget(rectToolButton);
    ui->toolBar->addWidget(selectToolButton);
    rectToolButton->setText("Rectangle");
    rectToolButton->setShortcut(QKeySequence("R"));
    selectToolButton->setText("Select");
    connect(rectToolButton, SIGNAL(clicked()), this, SLOT(newRectangleTool()));
    connect(selectToolButton, SIGNAL(clicked()), this, SLOT(newRectangleTool()));
    qApp->installEventFilter(this);
    setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::paintEvent(QPaintEvent*)
{
}

void MainWindow::newRectangleTool()
{
    RectangleTool* rectangleTool = new RectangleTool(static_cast<PaintingArea*>(mActivePA->widget()), mNavTool);
    activateTool(rectangleTool);
    deactivateTool(Tool::SELECTION_TOOL);
    connect(rectangleTool, SIGNAL(completed()), this, SLOT(switchBackToSelectionTool()));
}

void MainWindow::switchBackToSelectionTool()
{
    deactivateTool(Tool::RECTANGLE_TOOL);
    activateTool(new SelectionTool(static_cast<PaintingArea*>(mActivePA->widget()), mNavTool));
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::KeyPress == event->type())
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        std::vector<Tool*>& activeTools = getActiveTools();
        for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
        {
            Tool* tool = *it;
            if (tool)
            {
                tool->keyPressEvent(keyEvent, static_cast<PaintingArea*>(mActivePA->widget()));
            }
        }
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{

}

MainWindow::~MainWindow()
{
    delete mNavTool;
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    PaintingArea* pa = new PaintingArea(this);
    QMdiSubWindow* paSubWindow = ui->mdiArea->addSubWindow(pa);
    mNavTool = new NavigationTool(pa);
    activateTool(new SelectionTool(pa, mNavTool));
    activateTool(mNavTool);
    updateActivePA(paSubWindow);
    pa->show();
}

void MainWindow::deactivateTool(Tool::tool_type pToolType)
{
    //TODO: deal with case with tools of same type
    std::vector<Tool*>::iterator it = std::find_if(mActiveTools.begin(), mActiveTools.end(), [&](const auto& tool){return pToolType == tool->getToolType();});
    if (mActiveTools.cend() != it)
    {
        delete (*it);
        mActiveTools.erase(it);
    }
}

void MainWindow::activateTool(Tool* pTool)
{
    if (!findActiveTool(pTool->getToolType()))
    {
        mActiveTools.push_back(pTool);
    }
}

Tool* MainWindow::findActiveTool(Tool::tool_type pToolType)
{
    std::vector<Tool*>::iterator it = std::find_if(mActiveTools.begin(), mActiveTools.end(), [&](const auto& tool){return pToolType == tool->getToolType();});
    if (mActiveTools.cend() != it)
    {
        return *it;
    }
    else
    {
        return nullptr;
    }
}

void MainWindow::updateActivePA(QMdiSubWindow* pActivePA)
{
    mActivePA = pActivePA;
}
