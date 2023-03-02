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
    : QMainWindow(parent)
    , mUiState(NO_ACTIVE_TOOL_STATE), ui(new Ui::MainWindow), mPA(new PaintingArea(this)), mSelectionTool(mPA)
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
    mPA->setTool(&mSelectionTool);
    qApp->installEventFilter(this);

    XtBlock* xtblock = XtBlock::create();
}

void MainWindow::paintEvent(QPaintEvent*)
{
}

void MainWindow::newRectangleTool()
{
    if (mPA->getTool()->getToolType() == Tool::SELECTION_TOOL)
    {
        mSelectionTool.resetSelectionBox();
        mPA->update();
    }
    RectangleTool* rectangleTool = new RectangleTool(mPA);
    mPA->setTool(rectangleTool);
    connect(rectangleTool, SIGNAL(completed()), this, SLOT(switchBackToSelectionTool()));
}

void MainWindow::switchBackToSelectionTool()
{
    mPA->deleteTool();
    mPA->setTool(&mSelectionTool);
}

void MainWindow::newSelectionTool()
{
    mPA->setTool(&mSelectionTool);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    mPA->getTool()->keyPressEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

