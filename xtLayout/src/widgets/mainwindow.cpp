#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QToolButton>
#include "drawcommand.h"
#include "rectangletool.h"
#include "selectiontool.h"
#include "xtdb.h"
using namespace xtdb;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mPA(new PaintingArea(this))
{
    ui->setupUi(this);
    setCentralWidget(mPA);
    QToolButton *rectToolButton = new QToolButton(this);
    QToolButton *selectToolButton = new QToolButton(this);
    ui->toolBar->addWidget(rectToolButton);
    ui->toolBar->addWidget(selectToolButton);
    rectToolButton->setText("Rectangle");
    rectToolButton->setShortcut(QKeySequence("R"));
    selectToolButton->setText("Select");
    connect(rectToolButton, SIGNAL(clicked()), this, SLOT(newRectangleTool()));
    connect(selectToolButton, SIGNAL(clicked()), this, SLOT(newRectangleTool()));
    mPA->activateTool(new SelectionTool(mPA));
    qApp->installEventFilter(this);
}

void MainWindow::paintEvent(QPaintEvent*)
{
}

void MainWindow::newRectangleTool()
{
    RectangleTool* rectangleTool = new RectangleTool(mPA);
    mPA->activateTool(rectangleTool);
    mPA->deactivateTool(Tool::SELECTION_TOOL);
    connect(rectangleTool, SIGNAL(completed()), this, SLOT(switchBackToSelectionTool()));
}

void MainWindow::switchBackToSelectionTool()
{
    mPA->deactivateTool(Tool::RECTANGLE_TOOL);
    mPA->activateTool(new SelectionTool(mPA));
}

void MainWindow::newSelectionTool()
{
    mPA->activateTool(new SelectionTool(mPA));
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    std::vector<Tool*>& activeTools = mPA->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->keyPressEvent(event);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

